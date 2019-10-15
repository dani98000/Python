package il.co.ilrd.waitablequeue.codereview;

import java.util.Comparator;
import java.util.PriorityQueue;
import java.util.concurrent.Semaphore;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.TimeoutException;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

/** Using empty ctor for this function requires elements implementing comparable.
 *  If the ctor was used and was parameterized with a noncomparable element type.
 *  using WaitableQueue will result in class cast exception.*/
public class WaitableQueueSemaphore<T> implements WaitableQueue<T> {
	private PriorityQueue<T> queue;
	private Lock lock = new ReentrantLock();
	private Semaphore currentElements = new Semaphore(0);
	
	public WaitableQueueSemaphore() {
		queue = new PriorityQueue<>();
	}
	
	public WaitableQueueSemaphore(Comparator<? super T> comparator) {
		queue = new PriorityQueue<>(comparator);
	}
	
	@Override
	public void enqueue(T element) {
		lock.lock();
		queue.add(element);
		lock.unlock();
		currentElements.release();
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
		T retElement;
		
		if (!currentElements.tryAcquire(timeout, timeUnit)) {
			throw new TimeoutException("timeUnit" + timeUnit.name() + " "
					   + timeout + " dequeue Timed Out");
		}
		
		lock.lock();
		retElement = queue.poll();
		lock.unlock();
		
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
