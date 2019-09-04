package il.co.ilrd.vendingmachine;

public class TimeOutThread extends Thread {
	VendingMachine vm;

	TimeOutThread(VendingMachine vm) {
		this.vm = vm;
	}

	public void run() {
		while (true) {
			try {
				Thread.sleep(1000);
			} 
			catch (InterruptedException e) {
				break;
			}
			if(Thread.interrupted()) {
				break;
			}
			vm.timeOut();
		}
	}
}