package il.co.ilrd.concurrency;

import java.util.LinkedList;
import java.util.Queue;
import java.util.concurrent.Semaphore;


public class EX3Q3 {
	static Queue<Integer> list = new LinkedList<>();
	public static int i = 0;
	static Semaphore sem = new Semaphore(0);
	
	public static void produce() {
		System.out.println("Producing: " + i);
		list.add(i++);
	}
	
	public static void consume() {
		if(!list.isEmpty())
		System.out.println("Consuming: " + list.poll());
	}
	
	static class Producer extends Thread{
		@Override
		public void run() {
			while(true) {
				produce();
				sem.release();
				try {
					Thread.sleep(1000);
				} catch (InterruptedException e) {
					e.printStackTrace();
				}
			}
		}
	}
	
	static class Consumer extends Thread{
		@Override
		public void run() {
			while(true) {
				synchronized(EX3Q2.class){
					try {
						sem.acquire();
					} catch (InterruptedException e1) {
						e1.printStackTrace();
					}
					consume();
					try {
						Thread.sleep(1000);
					} catch (InterruptedException e) {
						e.printStackTrace();
					}
				}
			}
		}
	}
	
	public static void main(String[] args) {
		for (int i = 0; i < 5; ++i) {
			new Producer().start();;
		}
		
		for (int i = 0; i < 5; ++i) {
			new Consumer().start();;
		}
	}
}
