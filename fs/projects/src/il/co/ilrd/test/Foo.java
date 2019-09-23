package il.co.ilrd.test;

import java.util.ArrayList;
import java.util.List;
import java.util.Set;

public class Foo {
	public static void main(String[] args) {
		Integer[] intArray = {1,2,3,4,5};
		Character[] charArray = {'D','a','n','i','e','l'};
		Double[] doubleArray = {1.0,2.0,3.0,4.0,5.0}; 
		
		printArray(intArray);
		printArray(charArray);
		printArray(doubleArray);
	}
	
	class FooReference <T>{
	    private T t;
		
		public T get(){
			return t;
		}
		
		/*public set(T t) {
			
		}*/
	}

	
	public static <T> void printArray(T[] arr) {
		for(T element : arr) {
			System.out.print(element+",");
		}
		System.out.println();
	}
}
