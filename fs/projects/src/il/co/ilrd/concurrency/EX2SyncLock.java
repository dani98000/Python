package il.co.ilrd.concurrency;

import java.util.concurrent.locks.ReentrantLock;

import il.co.ilrd.concurrency.EX2Atomics.RunnableThread;

public class EX2SyncLock {
	static int globalCounter = 0;
	final static int INCREMENTBY = 10000000;
	static ReentrantLock reentrantlock = new ReentrantLock();
    
	static class RunnableThread implements Runnable{
		@Override
		public void run() {
			for(int i = 0; i < INCREMENTBY; ++i) {
			    reentrantlock.lock(); 
				++globalCounter;
			    reentrantlock.unlock(); 
			}
		}
	}
	
	public static void main(String[] args) throws InterruptedException {
		Thread counterThread1 = new Thread(new RunnableThread());
		Thread counterThread2 = new Thread(new RunnableThread());
		
		long start = System.currentTimeMillis();
		counterThread1.start();
		counterThread2.start();
		counterThread1.join();
		counterThread2.join();
		long end = System.currentTimeMillis();

		System.out.println(end - start);
		System.out.println(globalCounter);
	}
}
