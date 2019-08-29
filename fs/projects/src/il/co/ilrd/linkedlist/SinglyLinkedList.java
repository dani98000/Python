package il.co.ilrd.linkedlist;

public class SinglyLinkedList {
	private Node head;
	
	public Iterator begin() {
        Iterator iter = new ListIteratorImp(head); 
        
		return iter;
	}
	
	public boolean isEmpty() {
		return head == null;
	}
	
	public void pushFront(Object data) {
		Node new_node = new Node(data, head);		
		head = new_node;
	}
	
	public void popFront() {
		head = head.next;
	}
	
	public Iterator find(Object data) {
		
        Iterator currentIter = new ListIteratorImp(head); 
        Iterator prevIter = new ListIteratorImp(head);
		
        while (currentIter.hasNext()) {
        	if(currentIter.next() == data) {
   
        		return prevIter;
        	}
        	prevIter.next();
        }
		
        return null;
	}

	public int getSize() {
		Iterator iter = new ListIteratorImp(head);

		int size = 0;
		
		while (iter.hasNext()) {
			++size;
			iter.next();
        }
		
		return size;
	}
	
	private class Node {
		Object data;
		Node next;
		
		public Node(Object data, Node next) {
			this.next = next;
			this.data = data;
		}
	}
	
	private class ListIteratorImp implements Iterator {
		Node currNode;
		
		public ListIteratorImp(Node currNode) {
			this.currNode = currNode;
		}
		
		public boolean hasNext() {
			return (currNode != null);
		}

		public Object next() {
			Object retVal = currNode.data;
			currNode = currNode.next;
			
			return retVal;
		}
	}
}
