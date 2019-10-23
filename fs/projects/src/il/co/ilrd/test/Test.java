package il.co.ilrd.test;

import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class Test {
	public static void main(String[] args) {
		Pattern p = Pattern.compile("((e+)(e+)(e+))");
		Matcher matcher = p.matcher("yesh inbar ba heder");
		boolean res = matcher.find();
		System.out.println(res);
		res = matcher.find();
		System.out.println(res);
		System.out.println(matcher.groupCount());
		System.out.println(matcher.group(0));
	}
}

