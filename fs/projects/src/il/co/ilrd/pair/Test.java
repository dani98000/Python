package il.co.ilrd.pair;

import java.util.Comparator;

public class Test {
	public static void main(String[] args) {
		Integer[] arr = {1001,1000,5,0,1,4,9,4,65,421,0,1,-5,-7};
		Pair<Integer, Integer> p = Pair.minMax(arr);
		System.out.println(p);
		Pair<Integer, Integer> pair1 = Pair.of(5, 10);
		Pair<Integer, Integer> pair2 = Pair.of(5, 10);
		
		Comparator<Integer> c = Comparator.comparing((Integer x) -> x);
		System.out.println(Pair.minMax(arr, c));
	}
}
