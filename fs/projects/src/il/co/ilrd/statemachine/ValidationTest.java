package il.co.ilrd.statemachine;

public class ValidationTest {
	
	public static void run(String word) {
		States state = States.CHAR_READY;
		
		for (int i = 0; i < word.length(); i++) {
			if(state != States.ERROR) {
				state = state.checkValidity(word.charAt(i));	
			}
			else {
				System.out.println("Error!!!!");
			}
		}
	}
}
