package il.co.ilrd.vendingmachineV2;

public class Main {
	public static void main(String[] args) throws InterruptedException {
		Test.TestOnOff();
		Test.TestRegularUse();
		Test.TestNotEnoughMoney();
		Test.TestAddingProducts();
		Test.TestNoProduct();
		Test.TestMachineIsOff();
		Test.TestTimeOut();
	}
}