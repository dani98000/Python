package concurrency;

import java.util.concurrent.atomic.AtomicInteger;

public class EX2SyncBlock {
	static int globalCounter = 0;
	final static int INCREMENTBY = 10000000;
	AtomicInteger atomicGlobalCounter = new AtomicInteger(0);
	
	static class RunnableThread implements Runnable{
		@Override
		public void run() {
			synchronized(EX2SyncBlock.class) {
				for(int i = 0; i < INCREMENTBY; ++i) {
					++globalCounter;
				}
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
