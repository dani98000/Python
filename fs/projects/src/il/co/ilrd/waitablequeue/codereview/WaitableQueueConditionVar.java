package il.co.ilrd.waitablequeue.codereview;

import java.util.Comparator;


import java.util.PriorityQueue;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.TimeoutException;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

/** Using empty ctor for this function requires elements implementing comparable.
 *  If the ctor was used and was parameterized with a noncomparable element type.
 *  using WaitableQueue will result in class cast exception.*/
public class WaitableQueueConditionVar<T> implements WaitableQueue<T> {
    private PriorityQueue<T> queue;
    private Lock lock = new ReentrantLock();
    private Condition notEmptyCondition = lock.newCondition();

    public WaitableQueueConditionVar() {
    	queue = new PriorityQueue<>();
    }

    public WaitableQueueConditionVar(Comparator<? super T> comparator) {
    	queue = new PriorityQueue<>(comparator);
    }

    @Override
    public void enqueue(T element) {
    	lock.lock();
		queue.add(element);
		notEmptyCondition.signalAll();
		lock.unlock();
    }

    @Override
    public T dequeue() throws InterruptedException {
    	try {
			return dequeue(1000000000, TimeUnit.DAYS);
		} catch (TimeoutException e) {
		}
		
		return null;

    }

    @Override
    public T dequeue(long timeout, TimeUnit timeUnit) throws TimeoutException, InterruptedException {
    	T retElement = null;
    	
    	lock.lock();
    	try {
		    while (queue.isEmpty()) {
		    	boolean didTimeout = false;
		    	
				didTimeout = !notEmptyCondition.await(timeout, timeUnit);
		    	
		    	if (didTimeout) {
		    		throw new TimeoutException("timeUnit" + timeUnit.name() + " "
		    								   + timeout + " dequeue Timed Out");
		    	}
		    }
		    
		    retElement = queue.poll();
    	} finally {
    		lock.unlock();
    	}

        return retElement;

    }

    @Override
    public boolean remove(T element) {
    	boolean retBool = false;
		
		lock.lock();
		retBool =  queue.remove(element);
		lock.unlock();
		
		return retBool;
    }

}