import ol69.ws3.shapes.*;

public class Test {
	public static void main(String[] args) {
		
		Shape s1 = new Circle(5.5, "Red", false);
		System.out.println(s1);
		System.out.println(s1.getArea());
		System.out.println(s1.getPerimeter());
		System.out.println(s1.getColor());
		System.out.println(s1.isFilled());
		System.out.println(((Circle)s1).getRadius());
		
		System.out.println("\n\n");
		
		Circle c1 = (Circle)s1;
		System.out.println(c1);
		System.out.println(c1.getArea());
		System.out.println(c1.getPerimeter());
		System.out.println(c1.getColor());
		System.out.println(c1.isFilled());
		System.out.println(c1.getRadius());
		
		System.out.println("\n\n");
		
		/*Shape s2 = new Shape();*/
		
		Shape s3 = new Rectangle(1.0, 2.0, "RED", false);
		System.out.println(s3);
		System.out.println(s3.getArea());
		System.out.println(s3.getPerimeter());
		System.out.println(s3.getColor());
		System.out.println(((Rectangle)s3).getLength());		
		
		Shape s4 = new Square(5);
		System.out.println(s4);
		System.out.println(s4.getArea());
		System.out.println(s4.getPerimeter());
		System.out.println(s4.getColor());
		System.out.println(((Rectangle)s4).getLength());	
	}
}
