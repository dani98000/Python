package il.co.ilrd.exam.ds1;

import java.util.Stack;

public class StackExercises {
	public static void PrintReverseWords(String str) {
		Stack<Character>word = new Stack<>();
		
		for(int i = 0; i < str.length(); ++i) {
			if(Character.isWhitespace(str.charAt(i))) {
				while(!word.isEmpty()) {
					System.out.print(word.pop());
				}
				System.out.print(" ");
			}
			word.push(str.charAt(i));
		}
		
		while(!word.isEmpty()) {
			System.out.print(word.pop());
		}
	}

	public static Stack<Integer> SortStack(Stack<Integer> inputStack) {
		Stack<Integer> tempStack = new Stack<>();
		int temp = 0;
		
		while(!inputStack.isEmpty()) {
			temp = inputStack.pop();
			
			while(!tempStack.isEmpty() && tempStack.peek() < temp) {
				inputStack.push(tempStack.pop());
			}
			tempStack.push(temp);
		}
		
		return tempStack;
	}
}
