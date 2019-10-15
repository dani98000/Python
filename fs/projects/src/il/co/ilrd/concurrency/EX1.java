package il.co.ilrd.concurrency;

public class EX1 {
	public static void main(String[] args) {
		class SubThread extends Thread {
			public void run() {
				while(true) {
					System.out.println("Hey from Thread");
					try {
						Thread.sleep(500);
					} catch (InterruptedException e) {
						e.printStackTrace();
					}
				}
			}
	    }
			
		Thread subThread = new SubThread();
		subThread.start();
		try {
			Thread.sleep(1000);
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
		subThread.stop();
		
		Thread runnableThread = new Thread(new Runnable() {
			@Override
			public void run() {
				while(true) {
					System.out.println("Hey from Runnable");
					try {
						Thread.sleep(500);
					} catch (InterruptedException e) {
						e.printStackTrace();
					}
				}
			}
		});
		
		runnableThread.start();
		try {
			Thread.sleep(1000);
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
		runnableThread.stop();

	}
}
