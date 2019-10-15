package il.co.ilrd.concurrency;

import java.util.LinkedList;
import java.util.List;
import java.util.concurrent.Semaphore;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class EX3Q4 {
	static List<Integer> list = new LinkedList<>();
	public static int data = 0;
	public static final int NUM_CONSUMERS = 5;
	static Semaphore sem = new Semaphore(0);
	static Lock lock = new ReentrantLock();
	static Condition canConsume = lock.newCondition();
	
	public static void produce() {
		System.out.println("Producer producing data: " + data);
	}
	
	public static void consume() {
		System.out.println("Consumer consuming data: " + data);
	}
	
	static class Producer extends Thread{
		@Override
		public void run() {
			while(true) {
				for(int i = 0; i < NUM_CONSUMERS; ++i) {		
					sem.acquireUninterruptibly();
				}
				lock.lock();
				produce();
				canConsume.signalAll();
				lock.unlock();				
			}
		}
	}
	
	static class Consumer extends Thread{
		@Override
		public void run() {
			while(true) {
				lock.lock();
				sem.release();
				canConsume.awaitUninterruptibly();
				consume();
				lock.unlock();
			}
		}
	}
	
	public static void main(String[] args) throws InterruptedException {
		Producer producer = new Producer();
		producer.start();
		//producer.join();
		
		for (int i = 0; i < NUM_CONSUMERS; ++i) {
			new Consumer().start();
		}
		
		
	}
}
