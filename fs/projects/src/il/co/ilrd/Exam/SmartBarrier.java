package il.co.ilrd.Exam;

import java.util.concurrent.Semaphore;
import java.util.concurrent.atomic.AtomicInteger;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class SmartBarrier {
	private int numThreads;
	private Lock lock = new ReentrantLock();
	private Semaphore allDone;
	private Semaphore allOut;
	private AtomicInteger inCounter = new AtomicInteger(0);
	private AtomicInteger outCounter = new AtomicInteger(0);
	
	public SmartBarrier(int numThreads) {
		this.numThreads = numThreads;
		allOut = new Semaphore(numThreads);
		allDone = new Semaphore(0);
	}
	
	public void lock() throws InterruptedException {
		allOut.acquire();
		if(inCounter.incrementAndGet() == numThreads) {
			allDone.release(numThreads);
			inCounter.set(0);
		}
		allDone.acquire();
		if(outCounter.incrementAndGet() == numThreads) {
			allOut.release(numThreads);
			outCounter.set(0);;
		}
		
	}
	
	public static void main(String[] args) {
		SmartBarrier sb = new SmartBarrier(3);

		Thread t1 = new Thread(()->{
			while(true) {
				try {
					sb.lock();
				} catch (InterruptedException e1) {
					e1.printStackTrace();
				}
				System.out.println("this is thread1"); 
				try {
					Thread.sleep(3000);
				} catch (InterruptedException e) {
					e.printStackTrace();
				}
			}
		});
		
		Thread t2 = new Thread(()->{
			while(true) {
				try {
					sb.lock();
				} catch (InterruptedException e1) {
					e1.printStackTrace();
				}
				System.out.println("this is thread2"); 
				try {
					Thread.sleep(3000);
				} catch (InterruptedException e) {
					e.printStackTrace();
				}
			}
		});
		
		Thread t3 = new Thread(()->{
			while(true) {
				try {
					sb.lock();
				} catch (InterruptedException e1) {
					e1.printStackTrace();
				}
				System.out.println("this is thread3"); 
				try {
					Thread.sleep(3000);
				} catch (InterruptedException e) {
					e.printStackTrace();
				}
			}
		});
		
		t1.start();
		t2.start();
		t3.start();
	}
}
