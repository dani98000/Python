package il.co.ilrd.complexnumber;

import org.junit.Test;
import org.junit.jupiter.api.Assertions;

public class TestComplexNumber {

	private String getLineNumber(Exception e) {
        return "Line " + e.getStackTrace()[0].getLineNumber();
    }
	
	@Test
	public void testMultiply() {
		ComplexNumber num1 = new ComplexNumber(4,7);
		ComplexNumber num2 = new ComplexNumber(5,3);
		ComplexNumber res = new ComplexNumber(-1,47);
		
		Assertions.assertTrue(res.equals(num2.multiply(num1)), getLineNumber(new Exception()));
	}
	
	@Test
	public void testAdd() {
		ComplexNumber num1 = new ComplexNumber(4,7);
		ComplexNumber num2 = new ComplexNumber(5,3);
		ComplexNumber res = new ComplexNumber(9,10);
		
		Assertions.assertTrue(res.equals(num2.add(num1)), getLineNumber(new Exception()));
	}
	
	@Test
	public void testDivide() {
		ComplexNumber num1 = new ComplexNumber(4,7);
		ComplexNumber num2 = new ComplexNumber(5,3);
		ComplexNumber res = new ComplexNumber(1.2058823529411764, 0.6764705882352942);
				
		Assertions.assertTrue(res.equals(num1.divide(num2)), getLineNumber(new Exception()));
	}
	
	@Test
	public void testSubtract() {
		ComplexNumber num1 = new ComplexNumber(4,7);
		ComplexNumber num2 = new ComplexNumber(5,3);
		ComplexNumber res = new ComplexNumber(1,-4);
		
		Assertions.assertTrue(res.equals(num2.subtract(num1)), getLineNumber(new Exception()));
	}	
}