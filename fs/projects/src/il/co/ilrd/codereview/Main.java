package il.co.ilrd.codereview;

import java.util.Stack;

public class Main {
	public static void main(String[] args) {
		char[] arr = {'D','a','n','i','e','l'};
		CircularShift.ArrayShift(arr, 2);
		//System.out.print(arr);
		
		int[] arr2 = {1,9,8,4,0,0,2,7,0,6,0};
		Ex2.PushZerosToEnd(arr2);
		
		/*for(int i = 0;i < arr2.length; ++i) {
			System.out.print(arr2[i]+",");			
		}*/
		
		
		//StackExercises.PrintReverseWords("Hello World");
		
		Stack<Integer>inputStack = new Stack<>();
		int[] arr3 = {34,3,31,98,92,23};
		for(int i = 0; i < arr3.length; ++i) {
			inputStack.push(arr3[i]);
		}
		
		Stack<Integer>temp = new Stack<>();
		temp = StackExercises.SortStack(inputStack);
	
		/*while(!temp.isEmpty()) {
			System.out.print(temp.pop() + ",");
		}*/
	}
}
