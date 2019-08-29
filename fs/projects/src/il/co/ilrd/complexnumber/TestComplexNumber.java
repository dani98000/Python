package il.co.ilrd.complexnumber;

import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.DisplayName;
import org.junit.jupiter.api.Test;

class TestComplexNumber {

	private String getLineNumber(Exception e) {
        return "Line " + e.getStackTrace()[0].getLineNumber();
    }
	
	@Test
	@DisplayName("👹")
	void testMultiply() {
		ComplexNumber num1 = new ComplexNumber(4,7);
		ComplexNumber num2 = new ComplexNumber(5,3);
		ComplexNumber res = new ComplexNumber(-1,47);
		
		Assertions.assertTrue(res.equals(num2.multiply(num1)), getLineNumber(new Exception()));
	}
	
	@Test
	@DisplayName("👹")
	void testAdd() {
		ComplexNumber num1 = new ComplexNumber(4,7);
		ComplexNumber num2 = new ComplexNumber(5,3);
		ComplexNumber res = new ComplexNumber(9,10);
		
		Assertions.assertTrue(res.equals(num2.add(num1)), getLineNumber(new Exception()));
	}
	
	
}
