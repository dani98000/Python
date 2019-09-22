package il.co.ilrd.exam.ds1;

import java.io.IOException;
import org.junit.runner.JUnitCore;
import org.junit.runner.Result;
import org.junit.runner.notification.Failure;

import java.util.Stack;

public class Main {
	public static void main(String[] args) throws IOException {
		/*char[] arr = {'D','a','n','i','e','l'};
		CircularShift.ArrayShift(arr, 2);
		//System.out.print(arr);
		
		int[] arr2 = {1,9,8,4,0,0,2,7,0,6,0};
		Ex2.PushZerosToEnd(arr2);*/
		
		/*for(int i = 0;i < arr2.length; ++i) {
			System.out.print(arr2[i]+",");			
		}*/
		
		
		//StackExercises.PrintReverseWords("Hello World");
		
		/*Stack<Integer>inputStack = new Stack<>();
		int[] arr3 = {34,3,31,98,92,23};
		for(int i = 0; i < arr3.length; ++i) {
			inputStack.push(arr3[i]);
		}
		
		Stack<Integer>temp = new Stack<>();
		temp = StackExercises.SortStack(inputStack);*/
	
		/*while(!temp.isEmpty()) {
			System.out.print(temp.pop() + ",");
		}*/
		
		/*BST tree = new BST();
		
		tree.insert(4);
		tree.insert(2);
		tree.insert(5);
		tree.insert(1);
		tree.insert(3);*/
		//tree.reverseLevelOrder();
		//tree.printLevelOrder();
	
		//EX7.PrintReverseString("Daniel");
	
		//EX7.StringPermutations("eat");
	
		//Hash.listAnagramsFor("live");
		/*char[] a = {'A', 'B', 'A'};
		Graph graph = Graph.CreateGraph();
		graph.FindAllInstances(a);*/
		
		/*char[] nam2 = {'D','a','n','i','e','l'};
		char[] name = {'H','e','l','l','o'};

		CircularShift.ArrayShift2(name, 2);
		
		System.out.println(name);*/
		
		/*int[] arr = {10,12,11,15};
		Hash.PrintMissingElements(arr,10,15);*/
		
		JUnitCore core = new JUnitCore();
		Result result = core.run(TestExam.class);
				
		for (Failure failure : result.getFailures()) {
			System.out.println(failure);
		}
		
		if (result.wasSuccessful()) {
			System.out.println("Successful test!");
		}
		else {
			System.out.println("Test failed!");
		}
	}
}

