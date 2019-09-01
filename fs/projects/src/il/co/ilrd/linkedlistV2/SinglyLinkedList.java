package il.co.ilrd.linkedlistV2;

/** Creates a Singly linked list which works as a queue.*/
public class SinglyLinkedList {
	private Node head;
	
	public Iterator begin() {
		return new ListIteratorImp(head);
	}
	
	public boolean isEmpty() {
		return head == null;
	}
	
	public void pushFront(Object data) {
		head = new Node(data, head);
	}
	
	public void popBack() {
		Node runner = head;
		
		if(this.getSize() == 1) {
			head = null;
			
			return;
		}

		while(runner.next.next != null) {
			runner = runner.next;
		}
		
		
		runner.next = null;
	}

	/**
	 * Finds an object in the list.
	 * @param obj - this is the object being searched, compared using the function "equals".
	 * @return the iterator if found,else null.
	 */
	public Iterator find(Object obj) {
		
        Iterator currentIter = new ListIteratorImp(head); 
        Iterator prevIter = new ListIteratorImp(head);
		
        while (currentIter.hasNext()) {
        	if(obj.equals(currentIter.next())) {
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
		
		private ListIteratorImp(Node currNode) {
			this.currNode = currNode;
		}
		
		/** Returns true if the current iterator exists in the list. */
		public boolean hasNext() {
			return (currNode != null);
		}

		/** next returns the current object in the list */
		public Object next() {
			Object retVal = currNode.data;
			currNode = currNode.next;
			
			return retVal;
		}
	}
}
