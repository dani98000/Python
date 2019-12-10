package il.co.ilrd.test;

import static org.junit.Assert.assertArrayEquals;

import java.awt.print.Printable;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.LinkedList;
import java.util.List;

public class ArraysTest {
	private static int getNum(int[] arr, int from, int to) {
		int res = 0;
		int mult = 1;
		for(int i = to; i >= from; --i) {
			res += arr[i] * mult;
			mult *= 10;
		}
		
		return res;
	}
	
	public static void printSubsets(int[] arr) {
		int mult = 10;
		
		for(int extra = 0; extra < arr.length; ++extra) {
			System.out.println(arr[extra]);
			for(int i = 0; i < arr.length; ++i) {
				for(int j = i + 1; j < arr.length; ++j) {
					if(j+extra < arr.length) {
						System.out.println(arr[i]*mult+getNum(arr, j, j+extra));						
					}
				}
			}
			mult *= 10;
		}
	}
	
	public static void main(String[] args) {
		int[] arr = {1,2,3,4,5};
		printSubsets(arr);
	}
}
