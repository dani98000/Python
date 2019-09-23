package il.co.ilrd.genericlinkedlist;

import org.junit.runner.JUnitCore;
import org.junit.runner.Result;
import org.junit.runner.notification.Failure;

import il.co.ilrd.exam.ds1.TestExam;

public class Test {
	public static void main(String[] args) {
		JUnitCore core = new JUnitCore();
		Result result = core.run(TestExam.class);
		
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
