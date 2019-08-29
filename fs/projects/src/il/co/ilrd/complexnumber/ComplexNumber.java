package il.co.ilrd.complexnumber;

public class ComplexNumber implements Comparable <ComplexNumber> {
	double real;
	double imaginary;
	
	ComplexNumber(){
		this(0, 0);
	}
	
	ComplexNumber(double real, double imaginary){
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
    public boolean equals(Object o) { 
    	return (this.imaginary == ((ComplexNumber) o).getImaginary() && this.real == ((ComplexNumber) o).getReal());
    }
    
	@Override
	public int hashCode() {
		int result = 0;
		result = (int) (imaginary + real);
		
		return result;
	}
	
	@Override
	public String toString() {
		return this.real + " , " + this.imaginary + "i";
	}
	
	@Override
	public int compareTo(ComplexNumber o) {
	  if((imaginary == o.getImaginary() && 
		  real == o.getReal())) {
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

		imaginary = (-other.imaginary * real + imaginary * other.real) /
				(Math.pow(other.real, 2) + Math.pow(other.imaginary, 2));
		
		newReal = ((other.real * real + other.imaginary * imaginary) /
				(Math.pow(other.real, 2) + Math.pow(other.imaginary, 2)));
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
