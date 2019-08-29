package ol69.ws3.shapes;

public class Rectangle extends Shape{
	private double width;
	private double length;
	
	public Rectangle() {
		this.width = 1.0;
		this.length = 1.0;
	}
	
	public Rectangle(double width, double length) {
		this.width = width;
		this.length = length;
	}
	
	public Rectangle(double length, double width, String color, boolean filled) {
		super(color, filled);
		this.length = length;
		this.width = width;
	}

	public double getWidth() {
		return width;
	}

	public void setWidth(double width) {
		this.width = width;
	}

	public double getLength() {
		return length;
	}

	public void setLength(double length) {
		this.length = length;
	}
	
	public double getArea() {
		return width * length; 
	}
	
	public double getPerimeter() {
		return 2 * width + 2 * length;
	}
	
	@Override
	public String toString() {
		return "A Rectangle with width " + this.width + " ,and length " + this.length + " ,which is a subclass of "
				+ super.toString();
	}
}
