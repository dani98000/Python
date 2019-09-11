package il.co.ilrd.test;

public class Dog extends Animal{
	private int age = 1;
	
	public Dog(int a) {
		
		age = a;
		System.out.println(age);
		foo();
		System.out.println(age);
	}
	
	private void foo() {
		age = 5;
		System.out.println("I am a dog!");
	}
}
