package il.co.ilrd.vendingmachineV2;

import java.util.HashMap;

public interface VendingMachineController {
	public void setState(States state);
	public States getState();
	public void setBalance(int money);
	public void returnChange();
	public int getBalance();
	public void setTimer(int numSec);
	public int getTimer();
	public Monitor getMonitor();
	public void displayProducts();
	public HashMap<Integer, Product> getProducts();
}
