package il.co.ilrd.enums;

public class Test{
	EWeekDay day; 
	  
	    // Constructor 
	    public Test(EWeekDay day) 
	    { 
	        this.day = day; 
	    } 
	  
	    // Driver method 
	    public static void main(String[] args) 
	    { 
	        EWeekDay day = EWeekDay.FRIDAY;
	        System.out.println(day.getIntValue());
	        System.out.println(EWeekDay.fromValue(5));
	        EWeekDay.printAllValues();
	    } 
} 
