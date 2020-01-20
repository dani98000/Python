package il.co.ilrd.test;

import java.util.Arrays;

public class ArraysTest {
	private static int[] mergeSort(int[] arr) {
		if(arr.length <= 1) {
			return arr;
		}
		
		int[] temp1 = mergeSort(Arrays.copyOfRange(arr, 0, arr.length/2));
		int[] temp2 = mergeSort(Arrays.copyOfRange(arr, arr.length/2, arr.length));
		
		return merge(temp1, temp2);
	}
	
	public static int[] merge(int[] arr1, int[] arr2) {
		int[] temp = new int[arr1.length + arr2.length];
		
		int i = 0, j = 0, z = 0;
		
		while(i < arr1.length && j < arr2.length) {
			if(arr1[i] <= arr2[j]) {
				temp[z++] = arr1[i++];
			} else if(arr2[j] <= arr1[i]) {
				temp[z++] = arr2[j++];
			}
		}
		
		while(i < arr1.length) {
			temp[z++] = arr1[i++];
		}
		
		while(j < arr2.length) {
			temp[z++] = arr2[j++];
		}
				
		return temp;
	}
	
	public static void main(String[] args) {
		//int[] arr = {17,2,3,1,5,0};
		
		//System.out.println(Arrays.toString(ArraysTest.mergeSort(arr)));
	
		NameHolder instance1 = new NameHolder("Daniel");
		String name = "daniel";
		changeName(name);
		System.out.println(name);
	}
	
	private static void changeName(String holder) {
		holder = "Yoel";
	}
	
	private static class NameHolder {
		private String name;
		
		public NameHolder(String name) {
			this.name = name;
		}
		
		public void setName(String name) {
			this.name = name;
		}
		
		public String getName() {
			return name;
		}
	}
}
