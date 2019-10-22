package codewars;

<<<<<<< HEAD
public class Kata {
    public boolean isPalindrome(String s) {
        int i = 0;
        int j = s.length() - 1;
        
        while( i < j) {
        	while(i < j && !Character.isLetterOrDigit(s.charAt(i))) {
        		++i;
        	}
        	
        	while(i < j && !Character.isLetterOrDigit(s.charAt(j))) {
        		--j;
        	}
        	
        	if(Character.toLowerCase(s.charAt(i)) != Character.toLowerCase(s.charAt(j))) {
        		return false;
        	}
        }
        
        return true;
    }
=======
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
>>>>>>> e62c23ed6276c807523ff898a12a0dea0c29737d
}
