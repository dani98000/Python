package il.co.ilrd.complexnumber;

public class ComplexNumberTest {
	public static void main(String[] args) {
		ComplexNumber num1 = new ComplexNumber(4,7);
		ComplexNumber num2 = new ComplexNumber(5,3);
		
		System.out.println(num2.multiply(num1));
	}
}
