package il.co.ilrd.jarexercise;

public class Man implements Person{
	public void speak() {
		System.out.println("I am a man!");
	}
	public void eat(String food) {
		System.out.println("I am a man and my favorite food is: " + food);
	}
	public void exercise() {
		System.out.println("I am a man and i can't wait to go to the gym!!!");
	}
}
