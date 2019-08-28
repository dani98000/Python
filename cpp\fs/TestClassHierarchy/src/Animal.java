
public class Animal {
	private boolean vegetarian;

	private String eats;

	private int noOfLegs;

	// Instance Initialization Block 
    {  
        System.out.println("First instance block of superclass"); 
    } 
	
    // Constructor
	public Animal(){
		this.vegetarian = true;
		this.eats = "meat";
		this.noOfLegs = 5;
        System.out.println("Constructor of superclass called"); 		
	}
	
    // Static block
	static {
    System.out.println("static block of superclass called "); 
	}
	
	// Instance Initialization Block 
    {  
        System.out.println("Second instance block of superclass"); 
    } 
}
