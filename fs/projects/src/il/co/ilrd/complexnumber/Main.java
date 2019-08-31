package il.co.ilrd.complexnumber;

import org.junit.runner.JUnitCore;
import org.junit.runner.Result;
import org.junit.runner.notification.Failure;

public class Main {
	
	public static void main(String[] args) {
		JUnitCore core = new JUnitCore();
		Result result = core.run(TestComplexNumber.class);
				
		for (Failure failure : result.getFailures()) {
			System.out.println(failure);
		}
		
		if (result.wasSuccessful()) {
			System.out.println("Successful test!");
		}
		else {
			System.out.println("Test failed!");
		}
	}
}