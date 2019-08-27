
public class Child extends Parent{
    static { 
    	System.out.println("static block of Sub class is initialized in Java "); 
    }
    {
    	System.out.println("non static blocks in sub class is initialized");
    }
}
