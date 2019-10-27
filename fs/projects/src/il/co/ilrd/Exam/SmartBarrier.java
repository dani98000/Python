package il.co.ilrd.Exam;

import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class SmartBarrier {
	private int numThreads;
	private Lock lock = new ReentrantLock();
	private Condition isAllOut = lock.newCondition();
	int counter = 0;
	private int version = 0;
	private int i = 0;
	
	public SmartBarrier(int numThreads) {
		this.numThreads = numThreads;
	}
	
	public void lock() throws InterruptedException {
		lock.lock();
		if(i == version)
		{
			if(++counter == numThreads) {
				version += numThreads;
				counter = 0;
				isAllOut.signalAll();
			}else {
				while(i == version) {
					isAllOut.await();
					++i;
				}
			}
		}
		lock.unlock();
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
