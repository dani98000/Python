package il.co.ilrd.waitablequeue;

import static org.junit.jupiter.api.Assertions.*;

import java.util.concurrent.TimeUnit;
import java.util.concurrent.TimeoutException;

import org.junit.jupiter.api.Test;

class WaitableQueueSemaphoreTest {
	@Test
	void testEnqueue() throws InterruptedException {	
		WaitableQueue<Integer> queue = new WaitableQueueSemaphore<>();
		
		Thread t1 = new Thread(()-> {
			assertEquals(queue.dequeue(), 5);
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
		WaitableQueue<Integer> queue = new WaitableQueueSemaphore<>();
		
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
		WaitableQueue<Integer> queue = new WaitableQueueSemaphore<>();
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
		WaitableQueue<String> queue = new WaitableQueueSemaphore<>();
		
		Thread t1 = new Thread(()-> {
			String res = null;
			try {
				res = queue.dequeue(3000, TimeUnit.MILLISECONDS);
				assertEquals(res, "Daniel");
			}catch(TimeoutException e){
				fail();
			}
		});
		
		t1.start();
		queue.enqueue("Daniel");
	}
	
	@Test
	void testTimeout2() throws InterruptedException {	
		WaitableQueue<String> queue = new WaitableQueueSemaphore<>();
		
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
