
public class SinglyLinkedList {
	public Node head;
	
	public SinglyLinkedList(){
		this.head = null;
	}
	
	public Iterator begin() {
        Iterator iter = new ListIteratorImp(head); 
		return iter;
	}
	
	public boolean isEmpty() {
		if(this.getSize() == 0)
		{
			return true;
		}
		
		return false;
	}
	
	public void pushFront(Object data) {
		Node new_node = new Node(data, this);		
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
	
	public class Node{
		Object data;
		Node next;
		
		public Node(Object data, SinglyLinkedList list) {
			this.next = list.head;
			this.data = data;
		}
		
		public Object getData() {
			return data;
		}
		
		public Object getNext() {
			return this.next;
		}
		
	}
	
	private class ListIteratorImp implements Iterator{
		
		Node currNode;
		
		public ListIteratorImp(Node currNode) {
			this.currNode = currNode;
		}
		
		public boolean hasNext() {
			if(currNode == null)
			{
				return false;
			}
			
			return true;
		}

		public Object next() {
			Object retVal = currNode.data;
			currNode = currNode.next;
			
			return retVal;
		}
	}
}
