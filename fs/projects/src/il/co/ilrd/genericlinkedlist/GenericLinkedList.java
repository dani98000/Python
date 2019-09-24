package il.co.ilrd.genericlinkedlist;

import java.util.ConcurrentModificationException;
import java.util.Iterator;

public class GenericLinkedList <T> implements Iterable<T> {
	private Node<T> head;
	private ModCounter counter;
	
	public GenericLinkedList(){
		counter = new ModCounter();
	}
	
	public static class Node<U> {
		private U data;
		private Node<U> next;
		
		public Node(U data, Node<U> next) {
			this.data = data;
			this.next = next;
		}
		
		public Node<U> getNext() {
			return next;
		}
		
		public U getData() {
			return data;
		}
	}
	
	public void pushFront(T data) {
		head = new Node<T>(data, head);
		counter.increment();
	}
	
	public T popFront() {
		T data = head.data;
		head = head.getNext();
		counter.increment();
		
		return data;
	}
	
	public Iterator <T> find (T data) {
		Iterator<T> curr = iterator();
		Iterator<T> prev = iterator();

        while (curr.hasNext()) {
        	if(data.equals(curr.next())) {
        		return prev;
        	}
        	prev.next();
        }
		
        return null;
	}
	
	public int size() {
		Node<T> runner = head;
		int counter = 0;
		
		while (runner != null) {
			++counter;
			runner = runner.next;
        }
		
		return counter;
	}
	
	public boolean isEmpty() {
		return head == null;
	}
	
	//Utility Function for my tests... (This is why its package private)
	void displayList() {
		Node<T> runner = head;
		while(runner != null) {
			System.out.print(runner.data+"->");
			runner = runner.next;
		}
		System.out.println();
	}
	
	public static <S> GenericLinkedList<S> newReverse(GenericLinkedList<S>list) {
		GenericLinkedList<S>newList = new GenericLinkedList<>();
		
		Node<S> firstListRunner = list.head;

		while(firstListRunner != null) {
			newList.pushFront(firstListRunner.data);
			firstListRunner = firstListRunner.next;
		}
		
		return newList;
	}
	
	public static <S> GenericLinkedList<S> newMerge(GenericLinkedList<S>list1, GenericLinkedList<S>list2) {
		GenericLinkedList<S>newList = new GenericLinkedList<>();
		Node<S> firstListRunner = list1.head, secondListRunner = list2.head;
		
		while(firstListRunner != null) {
			newList.pushFront(firstListRunner.data);
			firstListRunner = firstListRunner.next;
		}
		
		while(secondListRunner != null) {
			newList.pushFront(secondListRunner.data);
			secondListRunner = secondListRunner.next;
		}
		
		newList = GenericLinkedList.newReverse(newList);
		
		return newList;
	}
	
	@Override
	public Iterator<T> iterator() {	
        Iterator<T> currentIter = new IteratorImpel<T>(head, counter); 

        return currentIter;
	}
	
	private static class IteratorImpel <V> implements Iterator<V> {
		Node<V> currNode;
		int currentCount;
		ModCounter expectedCount;
		
		private IteratorImpel(Node<V> currNode, ModCounter expected) {
			this.currNode = currNode;
			this.expectedCount = expected;
			currentCount = expected.counter;
		}
		
		/** Returns true if the current iterator exists in the list. */
		public boolean hasNext() throws ConcurrentModificationException {
			if(hasBeenModified()) {
				throw new ConcurrentModificationException();
			}
			
			return (currNode != null);
		}

		/** next returns the current V in the list */
		public V next() throws ConcurrentModificationException {
			if(hasBeenModified()) {
				throw new ConcurrentModificationException();
			}
			V retVal = currNode.data;
			currNode = currNode.next;
			
			return retVal;
		}
		
		public boolean hasBeenModified() {
			return (currentCount != expectedCount.counter);
		}
	}
	
	private static class ModCounter {
		private int counter = 0;
		
		public void increment() {
			++counter;
		}
	}
}
