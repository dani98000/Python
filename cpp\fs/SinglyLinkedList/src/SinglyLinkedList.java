
public class SinglyLinkedList {
	public Node head;
	private int size;
	
	public SinglyLinkedList(){
		this.head = null;
		this.size = 0;
	}
	
	public Node begin() {
		return head;
	}
	
	public boolean isEmpty() {
		if(size == 0)
		{
			return true;
		}
		
		return false;
	}
	
	public void pushFront(Object data) {
		Node new_node = new Node(data, this);		
		head = new_node;
		++size;
	}
	
	public void popFront() {
		head = head.next;
		--size;
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

	public int getSize(SinglyLinkedList list) {
		return this.size;
	}
	
	public class Node{
		Object data;
		Node next;
		
		public Node(Object data, SinglyLinkedList list) {
			this.next = list.begin();
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
		
		Node next;
		
		public ListIteratorImp(Node next) {
			this.next = next;
		}
		
		public boolean hasNext() {
			if(next == null)
			{
				return false;
			}
			
			return true;
		}

		public Object next() {
			Object retVal = next.data;
			next = next.next;
			
			return retVal;
		}
	}
}
