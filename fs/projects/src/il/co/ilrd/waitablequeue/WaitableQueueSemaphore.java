package il.co.ilrd.waitablequeue;
import java.util.Comparator;
import java.util.PriorityQueue;
import java.util.concurrent.Semaphore;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.TimeoutException;
import java.util.concurrent.locks.ReentrantLock;

public class WaitableQueueSemaphore<T> implements WaitableQueue<T> {
	private static int DEFAULT_INITIAL_CAPACITY = 11;
	private PriorityQueue<T> queue;
	private Semaphore sem = new Semaphore(0);;
	private ReentrantLock lock = new ReentrantLock();
	
	public WaitableQueueSemaphore() {
		queue = new PriorityQueue<>(DEFAULT_INITIAL_CAPACITY);
	}

	public WaitableQueueSemaphore(Comparator<? super T> comparator) {
		queue = new PriorityQueue<>(DEFAULT_INITIAL_CAPACITY, comparator);
	}

	@Override
	public void enqueue(T item) {
		lock.lock();
		try {
			queue.add(item);			
			sem.release();			
		} finally {
			lock.unlock();
		}
	}

	@Override
	public T dequeue() throws InterruptedException {
		T ret;			

		sem.acquire();
		lock.lock();
		try {
			ret = queue.poll();			
		} finally {
			lock.unlock();									
		}
	
		return ret;	
	}

	@Override
	public T dequeue(long timeout, TimeUnit timeUnit) throws TimeoutException,InterruptedException {
		T ret;
		
		if(!sem.tryAcquire(timeout, timeUnit)) {
			throw new TimeoutException();
		}				
		lock.lock();
		try {
			ret = queue.poll();			
		} finally {
			lock.unlock();									
		}
	
		return ret;	
	}

	@Override
	public boolean remove(T item) {
		boolean ret = false;
		
		lock.lock();
		try {
			if (sem.tryAcquire()) {
				if (!(ret = queue.remove(item))) {
					sem.release();
				}
			}
		} finally {
			lock.unlock();			
		}
		
		return ret;
	}
}
