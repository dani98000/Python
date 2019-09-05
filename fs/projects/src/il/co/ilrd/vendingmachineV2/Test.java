package il.co.ilrd.vendingmachineV2;

public class Test {
	public static void TestOnOff() {
		VendingMachine vm = new VendingMachine();

		vm.start();
		vm.stop();
	}

	public static void TestRegularUse() {
		VendingMachine vm = new VendingMachine();
		Product shoko = new Product(2, "Chocolate Milk");

		vm.start();

		vm.addProduct(shoko);

		vm.insertMoney(10);
		vm.chooseProduct("Chocolate Milk");
	}

	public static void TestNotEnoughMoney() {
		VendingMachine vm = new VendingMachine();
		Product shoko = new Product(2, "Chocolate Milk");

		vm.start();

		vm.addProduct(shoko);

		vm.insertMoney(1);
		vm.chooseProduct("Chocolate Milk");
	}

	public static void TestAddingProducts() {
		VendingMachine vm = new VendingMachine();
		Product shoko = new Product(2, "Chocolate Milk");

		vm.start();

		vm.addProduct(shoko);
		vm.insertMoney(2);
		vm.chooseProduct("Chocolate Milk");
	}

	public static void TestNoProduct() {
		VendingMachine vm = new VendingMachine();

		vm.start();

		vm.insertMoney(2);
		vm.chooseProduct("Tank");
	}

	public static void TestMachineIsOff() {
		VendingMachine vm = new VendingMachine();

		vm.start();
		vm.stop();

		vm.insertMoney(2);
		vm.chooseProduct("Tank");
	}

	public static void TestTimeOut() {
		VendingMachine vm = new VendingMachine();
		Product shoko = new Product(2, "Chocolate Milk");
		
		vm.start();
		
		vm.addProduct(shoko);
		vm.insertMoney(5);
		/*vm.chooseProduct("Chocolate Milk");
		vm.stop();*/
	}
}
