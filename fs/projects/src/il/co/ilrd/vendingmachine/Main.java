package il.co.ilrd.vendingmachine;

public class Main {
	public static void main(String[] args) {
		VendingMachine vm = new VendingMachine();
		Product coke = new Product(6, "coke");
		Product soda = new Product(4, "soda");
		Product water = new Product(3, "water");
	
		vm.start();
		vm.insertMoney(5);
		vm.chooseDrink(coke);
		vm.chooseDrink(soda);
	}
}