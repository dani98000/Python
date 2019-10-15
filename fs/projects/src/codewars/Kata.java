package codewars;

import java.util.Arrays;
import java.util.HashMap;
import java.util.LinkedHashMap;
import java.util.Map;
import java.util.Stack;

public class Kata {
    public static boolean isAnagram(String s, String t) {
        char[] a = s.toCharArray();
        Arrays.sort(a);
        char[] b = t.toCharArray();
        Arrays.sort(b);
        
        System.out.println(a);
        System.out.println(b);
        
        return Arrays.equals(a, b);
    }

	public static void main(String[] args) {
		System.out.println(Kata.isAnagram("eat", "ate"));
	}
}
