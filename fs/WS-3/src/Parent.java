
public class Parent {
    static { 
    	System.out.println("static block of Super class is initialized"); 
    }
    {
    	System.out.println("non static blocks in super class is initialized");
    }
}