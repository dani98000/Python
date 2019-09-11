package il.co.ilrd.test;

public class Animal {
	
	public Animal() {
		System.out.println("super is called.");
		foo();
	}
	
	private void foo() {
		System.out.println("I am an Animal!");
	}
}
