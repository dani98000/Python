package il.co.ilrd.enums;

public enum EWeekDay { 
    	SUNDAY, 
    	MONDAY, 
    	TUESDAY, 
    	WEDNESDAY, 
    	THURSDAY, 
    	FRIDAY, 
    	SATURDAY;
    	
    	public int getIntValue() {
    		return ordinal();
    	}
    	
    	public static EWeekDay fromValue(int value) {
    		return EWeekDay.values()[value];
    	}
    	
    	public static void printAllValues() {
    		for(EWeekDay day : EWeekDay.values()) {
    			System.out.println(day);
    		}
    	}
}

