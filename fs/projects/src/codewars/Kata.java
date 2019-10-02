package codewars;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.Comparator;
import java.util.List;
import java.util.stream.IntStream;

	public class Kata {
	    public static String camelCase(String str) {
	    	String ans = "";
	    	String[] ret= str.split(" ");
	    	for(int i = 0; i < ret.length; ++i) {
	    		ans += ret[i].substring(0,1).toUpperCase() + ret[i].substring(1);;
	    	}
	    	return ans;
	    }
		public static void main(String[] args) {
			String name = "==========h===yyyyyy===eeee=n==a========";
			name.replace(name.charAt(1), Character.toUpperCase(name.charAt(1)));
			System.out.println(name);
			System.out.println(Kata.camelCase("hello world"));
		}
}
