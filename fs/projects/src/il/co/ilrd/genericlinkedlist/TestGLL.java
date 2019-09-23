package il.co.ilrd.genericlinkedlist;

import static org.junit.Assert.assertTrue;
import static org.junit.jupiter.api.Assertions.assertThrows;

import java.util.ConcurrentModificationException;
import java.util.Iterator;

import org.junit.Test;

public class TestGLL {
	
	@Test
	public void TestReverse() {
		GenericLinkedList<Integer> list = new GenericLinkedList<>();
		list.PushFront(1);
		list.PushFront(2);
		list.PushFront(3);
		list.PushFront(4);
		list.PushFront(5);
		
		GenericLinkedList<Integer> listTest = GenericLinkedList.Reverse(list);
		listTest.DisplayList();
	}
	
	@Test
	public void TestMerge() {
		GenericLinkedList<Integer> list = new GenericLinkedList<>();
		list.PushFront(1);
		list.PushFront(2);
		list.PushFront(3);
		list.PushFront(4);
		list.PushFront(5);
		
		GenericLinkedList<Integer> list2 = new GenericLinkedList<>();
		list2.PushFront(6);
		list2.PushFront(7);
		list2.PushFront(8);
		list2.PushFront(9);
		list2.PushFront(10);
		
		GenericLinkedList<Integer> listTest = GenericLinkedList.Merge(list,list2);
		listTest.DisplayList();
	}
	
	@Test
	public void TestFind() {
		GenericLinkedList<Integer> list = new GenericLinkedList<>();
		list.PushFront(1);
		list.PushFront(2);
		list.PushFront(3);
		list.PushFront(4);
		list.PushFront(5);
		
		Iterator<Integer> a = list.Find(5);
		assertTrue(a.next() == 5);
	}
	
	@Test
	public void TestSize() {
		GenericLinkedList<Integer> list = new GenericLinkedList<>();
		list.PushFront(1);
		list.PushFront(2);
		list.PushFront(3);
		list.PushFront(4);
		list.PushFront(5);
		
		assertTrue(list.Size() == 5);
		
		list.PopFront();
		
		assertTrue(list.Size() == 4);
	}
	
	@Test
	public void FailFast() {
		GenericLinkedList<Integer> list = new GenericLinkedList<>();
		list.PushFront(1);
		list.PushFront(2);
		list.PushFront(3);
		list.PushFront(4);
		list.PushFront(5);
		
		Iterator<Integer> a = list.Find(5);
		
		list.PushFront(6);
		
	    assertThrows(ConcurrentModificationException.class, () -> {
	        a.next();
	    });
		

	}
}
	