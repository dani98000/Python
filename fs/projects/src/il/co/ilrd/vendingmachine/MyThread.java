package il.co.ilrd.vendingmachine;

public class MyThread extends Thread {
	VendingMachine vm;
	
	MyThread(VendingMachine vm){
		this.vm = vm;
	}
	
    public void run(){			
			while (!vm.ThreadShouldStop()) {
				try {
					Thread.sleep(1000);
				} catch (InterruptedException e) {
					e.printStackTrace();
				}
				vm.getState().checkTimeOut(vm);
			}
	}
  }