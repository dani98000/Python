package il.co.ilrd.genericlinkedlist;

import java.util.ConcurrentModificationException;
import java.util.Iterator;

public class GenericLinkedList <T> implements Iterable<T>{
	private Node<T> head;
	private ModCounter counter = new ModCounter();
	
	public static class Node<U> {
		private U data;
		private Node<U> next;
		
		public Node(U data, Node<U> next){
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
	
	public void PushFront(T data) {
		head = new Node<T>(data, head);
		counter.Increment();
	}
	
	public T PopFront() {
		T data = head.data;
		head = head.getNext();
		counter.Increment();
		
		return data;
	}
	
	public Iterator <T> Find (T data) {
		Node<T> nodeRunner = head;
		
        while (nodeRunner != null) {
        	if(data.equals(nodeRunner.data)) {
        		return iterator();
        	}
        	nodeRunner = nodeRunner.next;
        }
		
        return null;
	}
	
	public int Size() {
		Node<T> runner = head;
		int size = 0;
		
		while (runner != null) {
			++size;
			runner = runner.next;
        }
		
		return size;
	}
	
	public boolean IsEmpty(){
		return head == null;
	}
	
	public void DisplayList() {
		Node<T> runner = head;
		while(runner != null) {
			System.out.print(runner.data+"->");
			runner = runner.next;
		}
		System.out.println();
	}
	
	public static <S> GenericLinkedList<S> Reverse(GenericLinkedList<S>list){
		GenericLinkedList<S>newList = new GenericLinkedList<>();
		
		Node<S> firstListRunner = list.head;

		while(firstListRunner != null) {
			newList.PushFront(firstListRunner.data);
			firstListRunner = firstListRunner.next;
		}
		return newList;
	}
	
	public static <S> GenericLinkedList<S> Merge(GenericLinkedList<S>list1, GenericLinkedList<S>list2){
		GenericLinkedList<S>newList = new GenericLinkedList<>();
		Node<S> firstListRunner = list1.head, secondListRunner = list2.head;
		
		while(firstListRunner != null) {
			newList.PushFront(firstListRunner.data);
			firstListRunner = firstListRunner.next;
		}
		
		while(secondListRunner != null) {
			newList.PushFront(secondListRunner.data);
			secondListRunner = secondListRunner.next;
		}
		
		newList = GenericLinkedList.Reverse(newList);
		
		return newList;
	}
	
	@Override
	public Iterator<T> iterator(){	
        Iterator<T> currentIter = new IteratorImpel<T>(head, counter = new ModCounter()); 

        return currentIter;
	}
	
	private static class IteratorImpel <V> implements Iterator<V>{
		Node<V> currNode;
		ModCounter counter;
		
		private IteratorImpel(Node<V> currNode, ModCounter counter) {
			this.currNode = currNode;
			this.counter = counter;
		}
		
		/** Returns true if the current iterator exists in the list. */
		public boolean hasNext() {
			return (currNode != null);
		}

		/** next returns the current V in the list */
		public V next() {
			if(counter.HasBeenModified()) {
				throw new ConcurrentModificationException();
			}
			V retVal = currNode.data;
			currNode = currNode.next;
			
			return retVal;
		}
	}
	
	private static class ModCounter{
		private int counter = 0;
		
		public void Increment() {
			++counter;
		}
		
		public boolean HasBeenModified() {
			return (counter != 0);
		}
	}
}
