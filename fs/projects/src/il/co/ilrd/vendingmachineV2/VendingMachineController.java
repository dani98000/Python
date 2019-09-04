package il.co.ilrd.vendingmachineV2;

import java.util.HashMap;

import il.co.ilrd.vendingmachine.Product;

public interface VendingMachineController {
	public void setState(States state);
	public States getState();
	public void setBalance(int money);
	public void returnChange();
	public int getBalance();
	public void setTimer(int numSec);
	public Monitor getMonitor();
	public void displayProducts();
}
