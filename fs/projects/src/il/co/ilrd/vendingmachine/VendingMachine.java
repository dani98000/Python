package il.co.ilrd.vendingmachine;

import java.util.HashMap;

public class VendingMachine {
	private States stateVM;
	private int balance;
	private Monitor monitor;
	private static final int TIMEOUT = 3;
	private int counter;
	private Thread timerThread;
	
	HashMap<Integer, Product> hmap = new HashMap<Integer, Product>();

	public VendingMachine() {
		stateVM = States.INIT;
		monitor = new MonitorImpel();
	}
	
	//API
	public void insertMoney(int amount) {
		stateVM.insertMoney(amount, this);
	}

	public void chooseProduct(String productName) {
		stateVM.chooseProduct(productName, this);
	}

	public void start() {
		stateVM.start(this);
	}

	public void stop() {
		this.resetBalance();
		stateVM.stop(this);
	}
	
	public int getBalance() {
		return balance;
	}

	public void addProduct(Product prod) {
		monitor.print("adding the product: " + prod.getName());
		monitor.print("Products list:");
		hmap.put(prod.getName().hashCode(), prod);
		this.displayProducts();
	}

	private class MonitorImpel implements Monitor {
		public void print(String message) {
			System.out.println(message);
		}
	}
	
	private enum States {
		INIT {
			@Override
			protected void start(VendingMachine vm) {
				vm.timerThread = new Thread(new TimeOutThread(vm));
				vm.timerThread.start();
				System.out.println("< Welcome to the best Vending Machine in the whole entire WORLD! >");
				System.out.println("\t   < May i offer you something tasty? >");
				vm.displayProducts();
				System.out.println("===================================================================");

				vm.setState(WAITING_MONEY);
			}

			@Override
			protected void chooseProduct(String product, VendingMachine vm) {
				vm.monitor.print("Please press |START| before doing any operation.");
				vm.setState(INIT);
			}

			@Override
			protected void insertMoney(int money, VendingMachine vm) {
				vm.returnChange();
				vm.monitor.print("Please press |START| before doing any operation.");
				vm.setState(INIT);
			}

		},
		WAITING_MONEY {
			@Override
			protected void chooseProduct(String product, VendingMachine vm) {
				vm.monitor.print("Please insert money before choosing a product.");
				vm.setState(WAITING_MONEY);
			}

			@Override
			protected void insertMoney(int money, VendingMachine vm) {
				vm.addToBalance(money);
				vm.resetCounter();
				vm.setState(WAITING_CHOICE);
			}

		},
		WAITING_CHOICE {
			@Override
			protected void checkTimeOut(VendingMachine vm) {
				if (vm.checkCounter()) {
					vm.monitor.print("Timeout!");
					vm.returnChange();
					vm.setState(WAITING_MONEY);
				}
			}
			
			@Override
			protected void chooseProduct(String product, VendingMachine vm) {
				vm.resetCounter();
				
				// key exists
				if (vm.hmap.containsKey(product.hashCode())) {
					Product someProduct = vm.hmap.get(product.hashCode());

					if (someProduct.getPrice() <= vm.getBalance()) {
						vm.monitor.print("Congratz you got yourself a " + product);
						vm.subtractFromBalance(someProduct.getPrice());
						vm.returnChange();
					} else {
						vm.monitor.print("Not Enough Money, Dropping change.");
						vm.returnChange();
					}
				} else {
					// key does not exists
					vm.monitor.print("Sorry there is no such product");
				}
				vm.monitor.print("\t   < Thank you for buying, GoodBye =] >");
				vm.monitor.print("===================================================================\n");

				vm.setState(WAITING_MONEY);
			}

			@Override
			protected void insertMoney(int money, VendingMachine vm) {
				vm.addToBalance(money);
				vm.setState(WAITING_CHOICE);
			}
		};

		protected void stop(VendingMachine vm) {
			vm.monitor.print("\t\t\tGoodBye =]");
			vm.monitor.print("===================================================================\n");
			vm.timerThread.interrupt();		
			vm.resetCounter();
			vm.resetBalance();
			vm.setState(INIT);
		}

		protected void checkTimeOut(VendingMachine vm) {
			//Do absolutely nothing.
		}

		protected void start(VendingMachine vm) {
			//Do absolutely nothing.
		}
		
		protected abstract void insertMoney(int money, VendingMachine vm);
		protected abstract void chooseProduct(String product, VendingMachine vm);
	}

	private void setState(States newState) {
		stateVM = newState;
	}

	private void returnChange() {
		monitor.print("Dropping change: " + balance);
		balance = 0;
	}

	private void addToBalance(int money) {
		balance += money;
		monitor.print("Adding: " + money + " Now the balance is: " + balance);
	}

	private void subtractFromBalance(int money) {
		balance -= money;
		monitor.print("Subtracting: " + money + " Now the balance is: " + balance);
	}

	private void resetBalance() {
		balance = 0;
	}

	final public void displayProducts() {
		for (Integer key : hmap.keySet()) {
			String name = hmap.get(key).getName();
			int price = hmap.get(key).getPrice();
			monitor.print("Product: " + name + " - " + price);
		}
	}

	private boolean checkCounter() {
		if (this.counter > 0) {
			--this.counter;
			return false;
		}
		
		return true;
	}

	private void resetCounter() {
		counter = TIMEOUT;
	}

	final public void timeOut() {
		stateVM.checkTimeOut(this);
	}
}