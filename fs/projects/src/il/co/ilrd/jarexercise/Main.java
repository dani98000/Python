package il.co.ilrd.jarexercise;

public class Main {
	public static void main(String[] args) {
		Person daniel = new Man();
		Person inbar = new Woman();
		
		daniel.speak();
		daniel.eat("Pizza");
		
		inbar.speak();
		inbar.eat("Ice Cream");
	}

}
