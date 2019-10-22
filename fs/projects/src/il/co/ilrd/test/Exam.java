package il.co.ilrd.test;

import java.util.concurrent.Semaphore;

public class Exam {
	Semaphore ping = new Semaphore(1);
	Semaphore pong = new Semaphore(0);
	
	private class PingThread extends Thread {
		@Override
		public void run() {
			while(true) {
				try {
					ping.acquire();
				} catch (InterruptedException e) {
					e.printStackTrace();
				}
				System.out.println("ping");
				pong.release();
			}	
		}
	}
	
	private class PongThread extends Thread {
		@Override
		public void run() {
			while(true) {
				try {
					pong.acquire();
				} catch (InterruptedException e) {
					e.printStackTrace();
				}
				System.out.println("pong");
				ping.release();
			}	
		}
	}
	
	public static void main(String[] args) {
		Exam exam = new Exam();
		Thread pongThread = exam.new PongThread();
		Thread pingThread = exam.new PingThread();
		
		pongThread.start();
		pingThread.start();
	}
}

