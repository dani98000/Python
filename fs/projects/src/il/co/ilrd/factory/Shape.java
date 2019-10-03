package il.co.ilrd.factory;

import java.util.function.Function;

abstract class Shape implements Function<String ,String>{
	public String draw(String str) { return "Drawing Shape";}
}

class Circle extends Shape{	
	@Override
	public String draw(String str) {
		return "Drawing " + str;
	}

	@Override
	public String apply(String t) {
		return draw(t);
	}
	
	public static String draw2(String str) {
		return "Static Drawing " + str;
	}
}

