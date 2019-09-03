package il.co.ilrd.vendingmachine;

public class Test {
	public static void TestOnOff() {
		VendingMachine vm = new VendingMachine();
		
		vm.start();
		vm.stop();
	}
	
	public static void TestRegularUse() {
		VendingMachine vm = new VendingMachine();
		
		vm.start();
		
		vm.insertMoney(10);
		vm.chooseProduct("Cola");
	}
	
	public static void TestNotEnoughMoney() {
		VendingMachine vm = new VendingMachine();
		
		vm.start();
		
		vm.insertMoney(8);
		vm.chooseProduct("Sandwich");
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
	public static void TestTimeOut() throws InterruptedException {
		VendingMachine vm = new VendingMachine();
		vm.start();
		vm.insertMoney(5);
	}

	
}


