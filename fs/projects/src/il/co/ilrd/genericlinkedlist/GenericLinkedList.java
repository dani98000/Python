package il.co.ilrd.genericlinkedlist;

import java.util.Iterator;

public class GenericLinkedList <T> implements Iterable<T>{
	private Node head;
	
	public class Node{
		private T data;
		private Node next;
		
		public Node(T data, Node next){
			this.data = data;
			this.next = next;
		}
	}
	
	public void PushFront(T data) {
		head = new Node(data, head);
	}
	
	public T PopFront() {
		T data = head.data;
		head = head.next;
		
		return data;
	}
	
	public Iterator <T> Find (T data) {
        Iterator<T> currentIter = new IteratorImpel(head); 
        Iterator<T> prevIter = new IteratorImpel(head);
		
        while (currentIter.hasNext()) {
        	if(data.equals(currentIter.next())) {
        		return prevIter;
        	}
        	prevIter.next();
        }
		
        return null;
	}
	
	public int Size() {
		Node runner = head;
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
		Node runner = head;
		while(runner != null) {
			System.out.print(runner.data+"->");
			runner = runner.next;
		}
		System.out.println();
	}
	
	public static <T> GenericLinkedList<T> Reverse(GenericLinkedList<T>list){
		GenericLinkedList<T>.Node curr = list.head,prev = null,next;
		return list2;
		while(curr != null) {
			next = curr.next;
			curr.next = prev;
			prev = curr;
			curr = next;
		}
		
		list.head = prev;
		
		return list;
	}
	
	public static <T> GenericLinkedList<T> Merge(GenericLinkedList<T>list1, GenericLinkedList<T>list2){
		GenericLinkedList<T>.Node firstListRunner = list1.head, secondListHead = list2.head;
		return list2;
		
	}
	
	@Override
	public Iterator<T> iterator(){
		return null;}
	
	private class IteratorImpel implements Iterator<T>{
		Node currNode;
		
		private IteratorImpel(Node currNode) {
			this.currNode = currNode;
		}
		
		/** Returns true if the current iterator exists in the list. */
		public boolean hasNext() {
			return (currNode != null);
		}

		/** next returns the current T in the list */
		public T next() {
			T retVal = currNode.data;
			currNode = currNode.next;
			
			return retVal;
		}
	
	}
}
