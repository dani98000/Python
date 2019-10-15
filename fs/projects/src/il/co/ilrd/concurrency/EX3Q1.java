package il.co.ilrd.concurrency;

import java.util.concurrent.Semaphore;
import java.util.concurrent.atomic.AtomicReference;

public class EX3Q1 {
	static Semaphore consumerSem = new Semaphore(0);
	static Semaphore producerSem = new Semaphore(1);
	static String ping = "Ping";
	static AtomicReference<String> initialString = new AtomicReference<>(ping);
	
	static Thread producer = new Thread(()->{
		while(true) {
			try {
				producerSem.acquire();
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
			System.out.println(initialString.getAndSet("Pong"));
			try {
				Thread.sleep(1000);
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
			consumerSem.release();
		}
	});
	
	static Thread consumer = new Thread(()->{
		while(true) {
			try {
				consumerSem.acquire();
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
			initialString.set("Pong");
			System.out.println(initialString.getAndSet("Ping"));
			try {
				Thread.sleep(1000);
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
			producerSem.release();
		}
	
	});
	
	public static void main(String[] args) {
		producer.start();
		consumer.start();
	}

	
}
