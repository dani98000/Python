import org.junit.runner.JUnitCore;
import org.junit.runner.Result;

public class Test {
	public static void main(String[] args) {
		/*SinglyLinkedList list = new SinglyLinkedList();
		list.pushFront(5);
		list.pushFront(6);
		System.out.println(list.find(6).next());
		System.out.println(list.getSize());
		
	}*/
	
	 
	Result result = JUnitCore.runClasses(SLLTest.class);
	System.out.println(result.wasSuccessful());
	resultReport(result);
	}
		
	public static void resultReport(Result result) {
	    System.out.println("Finished. Result: Failures: " +
	      result.getFailureCount() + ". Ignored: " +
	      result.getIgnoreCount() + ". Tests run: " +
	      result.getRunCount() + ". Time: " +
	      result.getRunTime() + "ms.");
	}
}
