package il.co.ilrd.vendingmachineV2;

import java.util.HashMap;

import il.co.ilrd.vendingmachine.Product;

public class VendingMachine {
	private States stateVM;
	private int balance;
	private Monitor monitor;
	private int timeOutCounter;
	private Thread timerThread;
	private HashMap<Integer, Product> hmap;
	VendingMachineController controller;
	
	public VendingMachine() {
		timeOutCounter = 100;
		hmap = new HashMap<>();
		stateVM = States.INIT;
		monitor = new MonitorImpel();
		timerThread = new Thread(new TimeOutThread());
	}
	
	private class MonitorImpel implements Monitor {
		public void print(String message) {
			System.out.println(message);
		}
	}
	
	private class TimeOutThread extends Thread {
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
				VendingMachine.this.timeOut();
			}
		}
	}
	
	private class VMController implements VendingMachineController {
		public void setState(States state) {
			VendingMachine.this.stateVM = state;
		}
		
		public States getState() {
			return VendingMachine.this.stateVM;
		}
		
		public void setBalance(int balance) {
			VendingMachine.this.balance = balance;
		}
		
		public void returnChange() {
			VendingMachine.this.monitor.print("returning change: " + VendingMachine.this.balance);
			VendingMachine.this.balance = 0;
		}
		
		public int getBalance() {
			return VendingMachine.this.balance;
		}
		
		public void setTimer(int numSec) {
			VendingMachine.this.timeOutCounter = numSec;
		}
		
		public Monitor getMonitor() {
			return VendingMachine.this.monitor;
		}
		
		public void displayProducts() {
			for (Integer key : VendingMachine.this.hmap.keySet()) {
				String name = hmap.get(key).getName();
				int price = hmap.get(key).getPrice();
				monitor.print("Product: " + name + " - " + price);
			}
		}
	}
	
	//API
	public void insertMoney(int amount) {
		controller.getState().insertMoney(amount, VendingMachine.this.controller);
	}

	public void chooseProduct(String productName) {
		controller.getState().chooseProduct(productName, VendingMachine.this.controller);
	}

	public void start() {
		timerThread.start();
		controller.getState().start(controller);
	}

	public void stop() {
		controller.setBalance(0);
		controller.getState().stop(controller);
	}
	
	public int getBalance() {
		return balance;
	}

	public void addProduct(Product prod) {
		monitor.print("adding the product: " + prod.getName());
		monitor.print("Products list:");
		hmap.put(prod.getName().hashCode(), prod);
		controller.displayProducts();
	}
}
