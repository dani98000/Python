package il.co.ilrd.waitablequeue;

import static org.junit.jupiter.api.Assertions.*;

import java.util.concurrent.TimeUnit;
import java.util.concurrent.TimeoutException;

import org.junit.jupiter.api.Test;

class WaitableQueueConditionVarTest {
	@Test
	void testEnqueue() throws InterruptedException {	
		WaitableQueue<Integer> queue = new WaitableQueueConditionVar<>();
		
		Thread t1 = new Thread(()-> {
			try {
				assertEquals(queue.dequeue(), 5);
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
		});
		
		Thread t2 = new Thread(()-> {
			queue.enqueue(5);
		});
		
		t1.start();
		Thread.sleep(1000);
		t2.start();
	}
	
	@Test
	void testRemoveValid() throws InterruptedException {
		WaitableQueue<Integer> queue = new WaitableQueueConditionVar<>();
		
		Thread t1 = new Thread(()-> {
			queue.enqueue(5);
		});
	
		Thread t2 = new Thread(()-> {
			assertEquals(true, queue.remove(5));
		});
		
		t1.start();
		t2.start();
	}
	
	@Test
	void testRemoveNotValid() throws InterruptedException {
		WaitableQueue<Integer> queue = new WaitableQueueConditionVar<>();
		Thread t1 = new Thread(()-> {
			queue.enqueue(10);
		});
	
		Thread t2 = new Thread(()-> {
			assertEquals(false, queue.remove(5));
		});
		
		t1.start();
		t2.start();
	}

	
	@Test
	void testTimeout() throws InterruptedException {	
		WaitableQueue<String> queue = new WaitableQueueConditionVar<>();
		
		Thread t1 = new Thread(()-> {
			String res = null;
			try {
				res = queue.dequeue(3000, TimeUnit.MILLISECONDS);
				assertEquals(res, "Daniel");
			}catch(TimeoutException | InterruptedException e){
				fail();
			}
		});
		
		t1.start();
		queue.enqueue("Daniel");
	}
	
	@Test
	void testTimeout2() throws InterruptedException {	
		WaitableQueue<String> queue = new WaitableQueueConditionVar<>();
		
		long startTime = 0;
		
		try {
			startTime = System.currentTimeMillis();
			
			queue.dequeue(2, TimeUnit.SECONDS);
			fail();
		}catch(TimeoutException e) {
			assertEquals(2, (System.currentTimeMillis() - startTime) / 1000);
		}
		
		queue.enqueue("Daniel");
	
		try {
			startTime = System.currentTimeMillis();
			queue.dequeue(2, TimeUnit.SECONDS);
		}catch(TimeoutException e) {
			fail();
		}
		assertEquals(0, (System.currentTimeMillis() - startTime) / 1000);
	}
}