package il.co.ilrd.concurrency;

import java.util.Random;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.ScheduledExecutorService;
import java.util.concurrent.TimeUnit;

public class ExecutorFrameWorkEX2 {
	static class RunnableExample implements Runnable 
	{ 
		@Override
		public void run() {
			System.out.println("hey");
			try {
				Thread.sleep(1000);
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
		}
	} 
	


	public static void main(String[] args) {
		ExecutorService singleThreadPool = Executors.newSingleThreadExecutor();
		ExecutorService fixedThreadPoolOf3 = Executors.newFixedThreadPool(3);
		ExecutorService cachedThreadPool = Executors.newCachedThreadPool();
		ScheduledExecutorService scheduledThreadPool = Executors.newScheduledThreadPool(3);
		
		
		/*for(int i = 0; i < 3; ++i) {
			singleThreadPool.execute(new RunnableExample());	
		}*/
		
		/*for(int i = 0; i < 3; ++i) {
			fixedThreadPoolOf3.execute(new RunnableExample());	
		}*/
		
		/*for(int i = 0; i < 3; ++i) {
			cachedThreadPool.execute(new RunnableExample());	
		}*/
		
		for(int i = 0; i < 12; ++i) {
			scheduledThreadPool.schedule(()->{
				System.out.println("heyy");
				try {
					Thread.sleep(1000);
				} catch (InterruptedException e) {
					e.printStackTrace();
				}
			}, 3, TimeUnit.SECONDS);
		}

		//singleThreadPool.shutdown();
	}
}
