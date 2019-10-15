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
	Condition condition = lock.newCondition();
	
	public WaitableQueueConditionVar() {
		queue = new PriorityQueue<>(DEFAULT_INITIAL_CAPACITY);
	}

	public WaitableQueueConditionVar(Comparator<? super T> comparator) {
		queue = new PriorityQueue<>(DEFAULT_INITIAL_CAPACITY, comparator);
	}
	
	@Override
	public void enqueue(T item) {
		lock.lock();
		queue.add(item);
		condition.signalAll();			
		lock.unlock();			
	}

	@Override
	public T dequeue() {
		T ret = null;
		
		lock.lock();
		try {
			while(queue.isEmpty()) {
				condition.await();				
			}
			ret = queue.poll();
		} catch (InterruptedException e) {
			e.printStackTrace();
		}finally {
			lock.unlock();					
		}
		
		return ret;
	}

	@Override
	public T dequeue(long timeout, TimeUnit timeUnit) throws TimeoutException{
		T ret = null;
		lock.lock();
		try {
			while(queue.isEmpty()) {
				if(!condition.await(timeout, timeUnit)){
					throw new TimeoutException();
				}
			}
			ret = queue.poll();
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
		finally {
			lock.unlock();									
		}		
	
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