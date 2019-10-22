package il.co.ilrd.waitablequeue;

import java.util.concurrent.TimeUnit;
import java.util.concurrent.TimeoutException;

public interface WaitableQueue<T> {
	public void enqueue(T item);
	
	/**
	 * Blocking until there is an item to dequeue
	 * @return
	 * @throws InterruptedException 
	 */
	public T dequeue() throws InterruptedException;
	
	/**
	 * Blocking until there is an item to dequeue or until TimeOut.
	 * @return
	 * @throws InterruptedException 
	 */
	public T dequeue(long timeout, TimeUnit timeUnit) throws TimeoutException, InterruptedException;

	public boolean remove(T item);
}
