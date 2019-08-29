
public class Dog extends Animal{
	private String color;

	// Instance Initialization Block 
    {  
        System.out.println("First instance block of subclass"); 
    } 
	
    // Constructor 
	public Dog() {
		super();
		this.color="White";
        System.out.println("Constructor of subclass called"); 		
	}
	
	// Instance Initialization Block 
    {  
        System.out.println("Second instance block of subclass"); 
    } 
	
    // Static block
	static {
	    System.out.println("static block of subclass called "); 
	}
}