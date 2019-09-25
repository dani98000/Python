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
		list.pushFront(1);
		list.pushFront(2);
		list.pushFront(3);
		list.pushFront(4);
		list.pushFront(5);
		
		GenericLinkedList<Integer> listTest = GenericLinkedList.newReverse(list);
		listTest.displayList();
	}
	
	@Test
	public void TestMerge() {
		GenericLinkedList<Integer> list = new GenericLinkedList<>();
		list.pushFront(1);
		list.pushFront(2);
		list.pushFront(3);
		list.pushFront(4);
		list.pushFront(5);
		
		GenericLinkedList<Integer> list2 = new GenericLinkedList<>();
		list2.pushFront(6);
		list2.pushFront(7);
		list2.pushFront(8);
		list2.pushFront(9);
		list2.pushFront(10);
		
		GenericLinkedList<Integer> listTest = GenericLinkedList.newMerge(list,list2);
		listTest.displayList();
	}
	
	@Test
	public void TestFind() {
		GenericLinkedList<Integer> list = new GenericLinkedList<>();
		list.pushFront(1);
		list.pushFront(2);
		list.pushFront(3);
		list.pushFront(4);
		list.pushFront(5);
		
		Iterator<Integer> a = list.find(2);
		assertTrue(a.next() == 2);
		
		a = list.find(4);
		assertTrue(a.next() == 4);
		
		a = list.find(1);
		assertTrue(a.next() == 1);
		
		assertTrue(list.find(100) == null);
	}
	
	@Test
	public void TestSize() {
		GenericLinkedList<Integer> list = new GenericLinkedList<>();
		list.pushFront(1);
		list.pushFront(2);
		list.pushFront(3);
		list.pushFront(4);
		list.pushFront(5);
		
		assertTrue(list.size() == 5);
		
		list.popFront();
		
		assertTrue(list.size() == 4);
	}
	
	@Test
	public void FailFast() {
		GenericLinkedList<Integer> list = new GenericLinkedList<>();
		list.pushFront(1);
		list.pushFront(2);
		list.pushFront(3);
		list.pushFront(4);
		list.pushFront(5);
		
		Iterator<Integer> a = list.find(5);
		
		list.pushFront(6);
		
	    assertThrows(ConcurrentModificationException.class, () -> {
	        a.next();
	    });
		

	}
}
	