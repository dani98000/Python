
public class ClassInitializationTest {
    public static void main(String args[]){
    	 
        Unused o = null;
        Child t = new Child();
        System.out.println((Object)o == (Object)t);
    }
}
