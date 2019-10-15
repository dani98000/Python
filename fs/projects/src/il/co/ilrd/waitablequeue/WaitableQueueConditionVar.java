package il.co.ilrd.waitablequeue;

import java.util.Comparator;
import java.util.PriorityQueue;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.TimeoutException;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;


public class WaitableQueueConditionVar<T> implements WaitableQueue<T> {
	private static int DEFAULT_INITIAL_CAPACITY = 11;
	private PriorityQueue<T> queue;
	ReentrantLock lock = new ReentrantLock();
	Condition queueNotEmpty = lock.newCondition();
	
	public WaitableQueueConditionVar() {
		queue = new PriorityQueue<>(DEFAULT_INITIAL_CAPACITY);
	}

	public WaitableQueueConditionVar(Comparator<? super T> comparator) {
		queue = new PriorityQueue<>(DEFAULT_INITIAL_CAPACITY, comparator);
	}
	
	@Override
	public void enqueue(T item) {
		lock.lock();
		try {
			queue.add(item);
			queueNotEmpty.signalAll();						
		}finally {
			lock.unlock();						
		}
	}

	@Override
	public T dequeue() throws InterruptedException{
		T ret = null;
		
		lock.lock();
		try {
			while(queue.isEmpty()) {
				queueNotEmpty.await();				
			}
			ret = queue.poll();
		}finally {			
			lock.unlock();					
		}
		
		return ret;
	}

	@Override
	public T dequeue(long timeout, TimeUnit timeUnit) throws TimeoutException, InterruptedException{
		T ret = null;
		lock.lock();
		try {	
			while(queue.isEmpty()) {
				if(!queueNotEmpty.await(timeout, timeUnit)){
					throw new TimeoutException();
				}
			}	
			ret = queue.poll();
		}finally {
			lock.unlock();			
		}
	
		return ret;	
	}

	@Override
	public boolean remove(T item) {
		boolean ret = false;
		
		lock.lock();
		try {
			ret = queue.remove(item);			
		}finally {
			lock.unlock();			
		}
		
		return ret;
	}
}