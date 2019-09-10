package il.co.ilrd.jarexercise;

public class Woman implements Person{
	public void speak() {
		System.out.println("I am a woman!");
	}
	public void eat(String food) {
		System.out.println("I am a woman and my favorite food is: " + food);
	}
	public void exercise() {
		System.out.println("I am a woman and i can't wait to go to the gym!!!");
	}
}
