package il.co.ilrd.vendingmachine;

public interface State {
	public States stop();
	public States start();
	public abstract States chooseDrink();
	public abstract States insertMoney(int money);
}
