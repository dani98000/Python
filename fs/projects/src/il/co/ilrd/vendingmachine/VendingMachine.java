package il.co.ilrd.vendingmachine;

import java.util.HashMap;

public class VendingMachine {
	private States stateVM;
	private int balance;
	private Monitor monitor;
	private int timeOut;
	
    HashMap<Integer, Product> hmap = new HashMap<Integer, Product>();
	
	public VendingMachine() {
		stateVM = States.INIT;
		monitor = new MonitorImpel();
		
		Product Cola = new Product(5, "Cola");
		Product Water = new Product(3, "Water");
		Product Peanuts = new Product(3, "Peanuts");
		Product Sandwich = new Product(12, "Sandwich");
		
	    /*Adding elements to HashMap*/
	    hmap.put(Cola.getName().hashCode(), Cola);
	    hmap.put(Water.getName().hashCode(), Water);
	    hmap.put(Peanuts.getName().hashCode(), Peanuts);
	    hmap.put(Sandwich.getName().hashCode(), Sandwich);
	}
	
	public void insertMoney(int amount) {
		stateVM.insertMoney(amount, this);
		  MyThread myThread = new MyThread(this);
		  myThread.start();
	}
	
	public void chooseProduct(String productName){
		stateVM.chooseProduct(productName, this);
	}
	
	public void start() {
		stateVM.start(this);
	}
	
	public void stop() {
		this.resetBalance();
		stateVM.stop(this);
	}
	
	public void addProduct(Product prod) {
		monitor.print("adding the product: " + prod.getName());
		monitor.print("Products list:");
	    hmap.put(prod.getName().hashCode(), prod);
		this.displayProducts();
	}
	
	final private void returnChange() {
		monitor.print("Dropping change: " + balance);
		balance = 0;
	}
	
	final private void addToBalance(int money) {
		balance += money;
		monitor.print("Adding: " + money + " Now the balance is: " + balance);
	}
	
	final private void subtractFromBalance(int money) {
		balance -= money;
		monitor.print("Subtracting: " + money + " Now the balance is: " + balance);
	}
	
	public int getBalance() {
		return balance;
	}
	
	final private void resetBalance() {
		balance = 0;
	}
	
	public void displayProducts() {
		for (Integer key : hmap.keySet()){
            String name = hmap.get(key).getName();
            int price = hmap.get(key).getPrice();
            monitor.print("Product: " + name + " - " + price);  
		}
	}
	
	public enum States{	
		INIT{
			@Override
			public void start(VendingMachine vm) {
				System.out.println("< Welcome to the best Vending Machine in the whole entire WORLD! >");
				System.out.println("\t   < May i offer you something tasty? >");
				vm.displayProducts();
				System.out.println("===================================================================");

				vm.stateVM = WAITING_MONEY;
			}
			
			@Override
			public void chooseProduct(String product, VendingMachine vm) {
				vm.monitor.print("Please press |START| before doing any operation.");
				vm.stateVM = INIT;
			}
			
			@Override
			public void insertMoney(int money, VendingMachine vm) {
				vm.returnChange();
				vm.monitor.print("Please press |START| before doing any operation.");
				vm.stateVM = INIT;
			}

			
		}, WAITING_MONEY{
			@Override
			public void chooseProduct(String product, VendingMachine vm) {
				vm.monitor.print("Please insert money before choosing a product.");
				vm.stateVM = WAITING_MONEY;
			}
			
			@Override
			public void insertMoney(int money, VendingMachine vm) {
				vm.addToBalance(money);
				vm.stateVM = WAITING_CHOICE;
			}

			
		}, WAITING_CHOICE{
			@Override
			public void checkTimeOut(VendingMachine VM) {
				
			}
			
			@Override
			public void chooseProduct(String product, VendingMachine vm) {
				//key exists
				if (vm.hmap.containsKey(product.hashCode())) {
		            Product someProduct = vm.hmap.get(product.hashCode());
					if(someProduct.getPrice() <= vm.getBalance()) {
						vm.monitor.print("Congratz you got yourself a " + product);
						vm.subtractFromBalance(someProduct.getPrice());
						vm.returnChange();
		        	}
					else {
						vm.monitor.print("Not Enough Money, Dropping change.");
						vm.returnChange();
					}
				}
				else {
		            //key does not exists
					vm.monitor.print("Sorry there is no such product");
		        }
				vm.monitor.print("\t   < Thank you for buying, GoodBye =] >");
				vm.monitor.print("===================================================================\n");
	
				vm.stateVM = WAITING_MONEY;
			}
			
			@Override
			public void insertMoney(int money, VendingMachine vm) {			
				vm.addToBalance(money);
				vm.stateVM = WAITING_CHOICE;
			}
		};
		
		public void stop(VendingMachine vm) {
			vm.monitor.print("\t\t\tGoodBye =]");
			vm.monitor.print("===================================================================\n");
			
			vm.stateVM = INIT;
		}
		
		public void checkTimeOut(VendingMachine VM) {}
		public void start(VendingMachine vm) {}
		public abstract void insertMoney(int money, VendingMachine vm);
		public abstract void chooseProduct(String product, VendingMachine vm);
	}
	
	public class MonitorImpel implements Monitor{
		public void print(String message) {
			System.out.println(message);
		}
	}
}
