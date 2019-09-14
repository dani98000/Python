package il.co.ilrd.test;

class Dog extends Animal{
	private int age = 1;
	
	public Dog() {
		
		System.out.println("Dog constructor");
		super.foo();
	}
	
	
	
	public void foo() {
		System.out.println("I am a dog!");
	}
}

class Pitbull extends Dog
{
	public Pitbull() {
		
		System.out.println("Pitbull constructor");
	}
	
	
	
	public void foo() {
		System.out.println("I am a pitbull!");
	}	
}