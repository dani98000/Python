/**
*  @author  Daniel			
*  @version 01/09/2019 			     		
*/
package il.co.ilrd.complexnumber;

import java.math.BigDecimal;

public class ComplexNumber implements Comparable <ComplexNumber> {
	private double real;
	private double imaginary;
	
	ComplexNumber(){
		this(0.0, 0.0);
	}
	
	public  ComplexNumber(double real, double imaginary) {
		this.real = real;
		this.imaginary =imaginary;
	}

	public double getReal() {
		return real;
	}

	public void setReal(double real) {
		this.real = real;
	}

	public double getImaginary() {
		return imaginary;
	}

	public void setImaginary(double imaginary) {
		this.imaginary = imaginary;
	}
	
	public void setValue(double real, double imaginary) {
		this.real = real;
		this.imaginary = imaginary;
	}
	
	@Override
    public boolean equals(Object other) { 
        ComplexNumber num = (ComplexNumber)other;
        
        return 0.001 >= Math.abs(this.real - num.real) &&
               0.001 >= Math.abs(this.imaginary - num.imaginary);
	}
    
	@Override
	public int hashCode() {
		int result = 0;
		result = (int) (imaginary + real);
		
		return result;
	}
	
	@Override
	public String toString() {
		BigDecimal bdImg = new BigDecimal(imaginary);
		BigDecimal bdReal = new BigDecimal(real);
		
		bdReal = bdReal.setScale(3, BigDecimal.ROUND_HALF_DOWN);
        bdImg = bdImg.setScale(3, BigDecimal.ROUND_HALF_DOWN);
        
		String sign = (imaginary < 0)? " - " : " + ";
		
		return bdReal.toString() + sign + bdImg.abs().toString() + "i";
	}
	
	@Override
	public int compareTo(ComplexNumber other) {
	  if((imaginary == other.getImaginary() && 
		  real == other.getReal())) {
		  return 0;
	  }
	  
	  return 1;
	}
	
	public ComplexNumber add(ComplexNumber other) {
		imaginary += other.getImaginary();
		real += other.getReal();
		
		return this;
	}
	
	public ComplexNumber subtract(ComplexNumber other) {
		imaginary -= other.getImaginary();
		real -= other.getReal();
		
		return this;
	}
	
	public ComplexNumber divide(ComplexNumber other) {
		double newReal = real;
		
		newReal = ((other.real * real + other.imaginary * imaginary) /
				(Math.pow(other.real, 2.0) + Math.pow(other.imaginary, 2.0)));

		imaginary = (imaginary * other.real - other.imaginary * real) /
				(Math.pow(other.real, 2.0) + Math.pow(other.imaginary, 2.0));
		
		real = newReal;
		
		return this;
	}
	
	public ComplexNumber multiply(ComplexNumber other) {
		double newReal = real;
		
		newReal = (other.real * real - other.imaginary * imaginary);
		imaginary = (other.imaginary * real + other.real * imaginary);
		real = newReal;
		
		return this;
	}
}