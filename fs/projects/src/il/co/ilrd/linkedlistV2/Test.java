package il.co.ilrd.linkedlistV2;
import org.junit.runner.JUnitCore;
import org.junit.runner.Result;
import org.junit.runner.notification.Failure;

public class Test {
	public static void main(String[] args) {
		Result result = JUnitCore.runClasses(SLLTest.class);
		//System.out.println(result.wasSuccessful());
		//resultReport(result);
		for(Failure failure: result.getFailures()) {
			System.out.println(failure);
		}
	}
	
	
	public static void resultReport(Result result) {
	    System.out.println("Finished. Result: Failures: " +
	      result.getFailureCount() + ". Ignored: " +
	      result.getIgnoreCount() + ". Tests run: " +
	      result.getRunCount() + ". Time: " +
	      result.getRunTime() + "ms.");
	}
}