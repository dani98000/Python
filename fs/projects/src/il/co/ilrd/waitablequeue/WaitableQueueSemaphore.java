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
	Semaphore inQueue = new Semaphore(0);;
	ReentrantLock lock = new ReentrantLock();
	
	public WaitableQueueSemaphore() {
		queue = new PriorityQueue<>(DEFAULT_INITIAL_CAPACITY);
	}

	public WaitableQueueSemaphore(Comparator<? super T> comparator) {
		queue = new PriorityQueue<>(DEFAULT_INITIAL_CAPACITY, comparator);
	}

	@Override
	public void enqueue(T item) {
		lock.lock();
		queue.add(item);
		lock.unlock();
		inQueue.release();
	}

	@Override
	public T dequeue() {
		T ret;
		
		try {
			inQueue.acquire();
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
		
		lock.lock();
		ret = queue.poll();		
		lock.unlock();			
		
		return ret;
	}

	@Override
	public T dequeue(long timeout, TimeUnit timeUnit) throws TimeoutException {
		T ret;
		
		try {
			if(!inQueue.tryAcquire(timeout, timeUnit)){
				throw new TimeoutException();
			}				
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
		
		lock.lock();
		ret = queue.poll();
		lock.unlock();						
	
		return ret;	
	}

	@Override
	public boolean remove(T item) {
		lock.lock();
		boolean ret = queue.remove(item);
		lock.unlock();
		
		return ret;
	}
}
