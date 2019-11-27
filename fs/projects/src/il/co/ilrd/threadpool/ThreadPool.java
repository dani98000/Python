package il.co.ilrd.threadpool;

import java.util.Collections;
import java.util.Set;
import java.util.WeakHashMap;
import java.util.concurrent.*;
import java.util.concurrent.locks.*;

import il.co.ilrd.waitablequeue.WaitableQueue;
import il.co.ilrd.waitablequeue.WaitableQueueConditionVar;

public class ThreadPool implements Executor {
	private static final int DEFAULT_NUM_THREADS = 10;
	private static final Priority DEFAULT_PRIORITY = Priority.MEDIUM;
	private static final int HIGHEST_PRIORITY = 11;
	private static final int LOWEST_PRIORITY = 0;
	private int numThreads;
	
	private final WaitableQueue<Task<?>> taskQueue = new WaitableQueueConditionVar<>();
	private final Set<Worker> workers = Collections.newSetFromMap(new WeakHashMap<Worker, Boolean>());
	
	private ShutdownHandler ShutdownHandler = new ShutdownHandler(); 
	private PauseHandler pauseHandler = new PauseHandler();
	
	public ThreadPool() {
		this(DEFAULT_NUM_THREADS);
	}
	
	public ThreadPool(int numThreads) {
		if(numThreads < 0) {
			throw new IllegalArgumentException();
		}
		this.numThreads = numThreads;
		createWorkers(numThreads);
	}
	
	@Override
	public void execute(Runnable task) {
		submit(task, DEFAULT_PRIORITY);
	}
	
	public <T> Future<T> submit(Callable<T> callable, Priority priority) {
		if(callable == null) { throw new NullPointerException(); }
		if(ShutdownHandler.isActivated()) { throw new RejectedExecutionException(); }
		
		Task<T> newTask = new Task<T>(priority, callable);
		taskQueue.enqueue(newTask);	
		
		return newTask.getFuture();	
	}
	 
	public <T> Future<T> submit(Callable<T> callable) {
		return submit(callable, DEFAULT_PRIORITY);
	}
	
	public <T> Future<T> submit(Runnable runnable, Priority priority) {
		return submit(Executors.callable(runnable, null),priority);
	}
	
	public <T> Future<?> submit(Runnable runnable, Priority priority, T result) {
		return submit(Executors.callable(runnable, result),priority);
	}
	
	public <T> void setNumThreads(int newNumThreads) {
		if (newNumThreads > numThreads) {
			if (pauseHandler.isPaused()) {
				pauseHandler.enqueuePausingTasks(newNumThreads-numThreads);
			}
			createWorkers(newNumThreads - numThreads);
		} else if (newNumThreads < numThreads) {
			for (int i = 0; i < numThreads - newNumThreads; ++i) {
				taskQueue.enqueue(createSuicideTask());
			}
		}
		numThreads = newNumThreads;
	}
	
	public <T> void pause() {
		pauseHandler.pause();
	}

	public <T> void resume() {
		pauseHandler.resume();
	}

	public <T> void shutdown() {
		ShutdownHandler.shutdown();
	}
	
 	public boolean awaitTermination(long timeout, TimeUnit unit) throws InterruptedException {
 		return ShutdownHandler.awaitTermination(timeout, unit);
 	}
	
	private <T> Task<T> createSuicideTask() {		
		return new Task<T>(HIGHEST_PRIORITY,() -> {
			((Worker)Thread.currentThread()).shouldStop = true;
			
			return null;
		});
	}
	
	private class Worker extends Thread {
		private boolean shouldStop = false;
		
		@Override
		public void run() {
			while (!shouldStop) {
				try {
					Task<?> task = taskQueue.dequeue();
					task.execute();
				} catch (InterruptedException e) {
					// worker should keep on working while shouldStop equals false
				}
			}
		}
	}
	
	private class Task<T> implements Comparable<Task<?>> {
		private final int priority;
		private final Callable<T> callable; 
		private final TaskFuture taskFuture;
		
		public Task(Priority priority, Callable<T> callable) {
			this.priority = priority.getPriority();
			this.callable = callable;
			taskFuture = new TaskFuture();
		}
		
		private Task(int priority, Callable<T> callable) {
			this.priority = priority;
			this.callable = callable;
			taskFuture = new TaskFuture();
		}
		
		public void execute() {
			try {
				taskFuture.result = callable.call();	
			} catch (Exception e) {
				taskFuture.isFailed = true;
				taskFuture.failureCause = e;
			} finally {
				taskFuture.isDone = true;
				taskFuture.isResultReady.release();
			}
		}
		
		public Future<T> getFuture() {
			return taskFuture;
		}
		
		@Override
		public int compareTo(Task<?> other) {
			return other.priority - priority; 
		}
		
		private class TaskFuture implements Future<T> {
			private T result;
			private boolean isDone = false;
			private boolean isCancelled = false;
			private boolean isFailed = false;
			private Semaphore isResultReady = new Semaphore(0);
			private Exception failureCause = null;		

			@Override
			public boolean cancel(boolean mayInterruptIfRunning) {
				boolean result = true;
				
				// Ignores the parameter. We don't support canceling running tasks.
				if (!isCancelled) {
					if ((result = getTaskQueue().remove(Task.this)) == true) {
						isCancelled = true;
						isDone = true;
					}
				}
				
				return result;
			}

			@Override
			public T get() throws InterruptedException, ExecutionException {
				try {
					return get(Long.MAX_VALUE, TimeUnit.DAYS);
				} catch (TimeoutException e) {
					throw new Error("An error with the system timer has occurred!");
				}
			}

			@Override
			public T get(long timeout, TimeUnit timeunit) throws InterruptedException, TimeoutException, ExecutionException {
				if (!isDone) {
					if (!isResultReady.tryAcquire(timeout, timeunit)) {
						throw new TimeoutException();
					}
					isResultReady.release();
				}
				if (isFailed) {
					throw new ExecutionException("Failure",failureCause);
				}
				
				return result;
			}

			@Override
			public boolean isCancelled() {
				return isCancelled;
			}

			@Override
			public boolean isDone() {
				return isDone;
			}
		}
	}
	
	private class PauseHandler {
		boolean isPaused = false;
		Semaphore pauseSemaphore = new Semaphore(0);
		
		public boolean isPaused() {
			return isPaused;
		}
		
		public <T> void pause() {
			pauseSemaphore.drainPermits();
			isPaused = true;
			enqueuePausingTasks(numThreads);
		}
		
		private <T> void enqueuePausingTasks(int numTasks) {
			for (int i = 0; i < numTasks; ++i) {
				taskQueue.enqueue(new Task<T>(HIGHEST_PRIORITY,() -> {
					pauseSemaphore.acquire();					
					return null;
				}));		
			}
		}
		
		public <T> void resume() {
			isPaused = false;
			pauseSemaphore.release(workers.size());
		}
	}
	
	private class ShutdownHandler {
		private boolean isShutdown = false;
		
		public void shutdown() {
			isShutdown = true;
			for (int i = 0; i < numThreads; ++i)
			{
				taskQueue.enqueue(new Task<>(LOWEST_PRIORITY,() -> {
					((Worker)Thread.currentThread()).shouldStop = true;
					return null;
				}));		
			}		
		}
		
	 	public boolean awaitTermination(long timeout, TimeUnit unit) throws InterruptedException {
	 		timeout = TimeUnit.MILLISECONDS.convert(timeout, unit);
	 		for(Worker worker : getWorkers()) {
	 			if(timeout <= 0) {
	 				return false;
	 			}
	 			long startTime = System.currentTimeMillis();
	 			worker.join(timeout);
	 			timeout -= (System.currentTimeMillis() - startTime);
	 		}
	 		
	 		return true;
	 	}
		
		public boolean isActivated() {
			return isShutdown;
		}
	}
	
	private WaitableQueue<Task<?>> getTaskQueue() { return taskQueue; }
	
	private void createWorkers(int numWorkers) {
		for (int i = 0; i < numWorkers; ++i) {
			Worker newWorker = new Worker();
			workers.add(newWorker);
			newWorker.start();
		}
	}
	
	private Set<Worker> getWorkers(){
		return workers;
	}
	
	public enum Priority {
		HIGH(10),
		MEDIUM(5),
		LOW(1);
		
		private final int priority;
		
		Priority(int priority) {
			this.priority = priority;
		}
		
		public int getPriority() {
			return priority;
		}
	}
}