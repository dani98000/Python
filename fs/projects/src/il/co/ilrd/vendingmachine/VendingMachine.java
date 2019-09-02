package il.co.ilrd.vendingmachine;

public class VendingMachine {
	public States stateVM;
	int balance;
	
	public VendingMachine() {
		this.stateVM = States.INIT;
	}
	
	public void insertMoney(int money) {
		balance += money;
		stateVM = stateVM.insertMoney(money);
		System.out.println("Current balance is: " + balance);
	}
	
	public void chooseDrink(Product drink) {
		if (drink.getPrice() <= balance) {
			balance -= drink.getPrice();
			stateVM = stateVM.chooseDrink();
			System.out.println("Congratz you got yourself a " + drink.getName());
			System.out.println("Current balance is: " + balance);
		}
		else {
			System.out.println("Sorry not enough money, please insert more coins.");
			return;
		}
	}
	
	public void start() {
		stateVM.start();
	}
	
	public void stop() {
		stateVM.stop();
	}
}
