package ol69.ws3.shapes;
public abstract class Shape {
	private boolean filled;
	private String color;
	
	public Shape() {
		super();
		color = "green";
		filled = true;
	}
	
	public Shape(String color, boolean filled) {
		super();
		this.filled = filled;
		this.color = color;
	}

	@Override
	public String toString() {
		return "A Shape with color of " + this.color + " and " + (this.filled ? "filled" : "Not filled");
	}

	public boolean isFilled() {
		return filled;
	}

	public void setFilled(boolean filled) {
		this.filled = filled;
	}

	public String getColor() {
		return color;
	}

	public void setColor(String color) {
		this.color = color;
	}

	public abstract double getArea();
	public abstract double getPerimeter();

}
