package il.co.ilrd.concurrency;

import java.util.LinkedList;
import java.util.Queue;

public class EX3Q2 {
	static Queue<Integer> list = new LinkedList<>();
	public static int i = 0;
	
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
				try {
					Thread.sleep(1000);
				} catch (InterruptedException e) {
					// TODO Auto-generated catch block
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
					consume();
					try {
						Thread.sleep(1000);
					} catch (InterruptedException e) {
						// TODO Auto-generated catch block
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
