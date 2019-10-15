package il.co.ilrd.concurrency;

import java.util.Random;
import java.util.concurrent.Callable;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;
import java.util.concurrent.FutureTask;
import java.util.concurrent.ThreadPoolExecutor;

public class ExecuterFrameworkTest {
	static class CallableExample implements Callable 
	{ 
	    public Object call() throws Exception 
	    { 
	        Random generator = new Random(); 
	        Integer randomNumber = generator.nextInt(5); 
	        Thread.sleep(randomNumber * 1000); 
	  
	        return randomNumber; 
	    } 
	} 
	
	public static void main(String[] args) throws InterruptedException, ExecutionException {
		ExecutorService executor = Executors.newFixedThreadPool(1);
		Callable task = new CallableExample();
		Future<Integer> future = executor.submit(task);
		System.out.println("future done? " + future.isDone());

		Integer result = future.get();

		System.out.println("future done? " + future.isDone());
		System.out.print("result: " + result);
	}
}
	
	
	
	
