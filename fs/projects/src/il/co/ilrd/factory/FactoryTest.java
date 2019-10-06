package il.co.ilrd.factory;

import static org.junit.jupiter.api.Assertions.*;

import java.util.function.Function;

import org.junit.jupiter.api.Test;

public class FactoryTest {
	@Test
	void test() {
		Factory<Integer,String,String> fac = new Factory<>();
		fac.add(1, (String str)->new Circle().apply(str));
		fac.add(2, new Circle() {
			@Override
			public String apply(String t) {
				return draw(t);
			}});
		
		fac.add(3, Circle::draw2);
		fac.add(4, new Circle()::draw);
		fac.add(5, String::intern);
		
		System.out.println(fac.create(1,"Circle"));
		System.out.println(fac.create(2,"Circle"));
		System.out.println(fac.create(3,"Circle"));
		System.out.println(fac.create(4,"Circle"));
		System.out.println(fac.create(5,"Daniel"));
	}

}
