package il.co.ilrd.exam.ds1;

public class SinglyLinkedList {    
    class Node{    
        int data;    
        Node next;    
            
        public Node(int data) {    
            this.data = data;    
            this.next = null;    
        }    
    }    
     
    private Node head = null;    
    private Node tail = null;    
        
    public void addNode(int data) {    
        Node newNode = new Node(data);    
            
        if(head == null) {    
            head = newNode;    
            tail = newNode;    
        }    
        else {    
            tail.next = newNode;    
            tail = newNode;    
        }    
    }
    
    private int getSize() {
    	Node temp = head;
    	int counter = 0;
    	
    	while(temp != null) {
    		++counter;
    		temp = temp.next;
    	}
    	
    	return counter;
    }
        
    public void display() {    
        Node current = head;    
            
        if(head == null) {    
            System.out.println("List is empty");    
            return;    
        }    
        System.out.println("Nodes of singly linked list: ");    
        while(current != null) {    
            System.out.print(current.data + " ");    
            current = current.next;    
        }    
        System.out.println();    
    }
    
    public void createLoop(int index) {
    	int counter = 0;
    	Node temp = head;
    	Node loopNode = head;
    	
    	for(int i = 0; i < this.getSize()-1; ++i) {
    		if(i == index) {
    			loopNode = temp;
    		}
    		temp = temp.next;
    	}
    	
    	temp.next = loopNode;
    }
    
    public boolean HasLoop() {
    	return (DetectLoop() != null); 
    }
    
    private Node DetectLoop() {
    	Node fast = head.next;
    	Node slow = head;
    	
    	while(fast != null) {
    		if(slow == fast) {
    			return slow;
    		}
    		
    		slow = slow.next;
    		fast = fast.next;
    		if(fast == null) {
    			break;
    		}
    		fast = fast.next;
    	}
    	
    	return null;
    }
    
    public void OpenLoop() {
    	Node fast = head.next;
    	Node slow = head;;
    	Node loopNode = DetectLoop();
		Node curr = loopNode;

		while(true) {
    		while(curr.next != loopNode && loopNode.next != head) {
    			curr = curr.next;
    		}
    		
    		if(curr.next == head) {
    			break;
    		}
   
    		head = head.next;
    	}
		
		curr.next = null;
    }
    
    public static void CreateIntersecedLists(SinglyLinkedList sll1, SinglyLinkedList sll2) {
    	Node intersectionPoint = sll1.head;
    	int counter = 0;
    			
    	while(counter < 2) {
    		intersectionPoint = intersectionPoint.next;
    		++counter;
    	}
    	
    	Node curr = sll2.head;

    	while(curr.next != null) {
    		curr = curr.next;
    	}
    	
    	curr.next = intersectionPoint;
    }
    
    public static boolean hasIntersection(SinglyLinkedList sll1, SinglyLinkedList sll2) {
    	Node runner1 = sll1.head;
    	Node runner2 = sll2.head;
    	
    	while(runner1.next != null) {
    		runner1 = runner1.next;
    	}
    	
    	while(runner2 != null) {
    		if(runner1 == runner2) {
    			return true;
    		}
    		runner2 = runner2.next;
    	}
    	    	
    	return false;
    }
    
    public static void seperateIntersectedLoops(SinglyLinkedList sll1, SinglyLinkedList sll2) {
    	int size1 = sll1.getSize();
    	int size2 = sll2.getSize();
    	Node head1 = sll1.head;
    	Node head2 = sll2.head;
    	
    	if(size1 < size2) {
    		while(size1 != size2) {
    			head2 = head2.next;
    			--size2;
    		}
    	}else {
    		while(size1 != size2) {
    			head1 = head1.next;
    			--size1;
    		}
    	}
    	
    	while(head1.next != head2.next) {
    		head1 = head1.next;
    		head2 = head2.next;
    	}
    	
    	head1.next = null;
    }
    
    public static void main(String[] args) {
    	SinglyLinkedList sll1= new SinglyLinkedList();
    	sll1.addNode(1);
    	sll1.addNode(2);
    	sll1.addNode(3);
    	sll1.addNode(4);
    	sll1.addNode(5);
    	
    	/*sll1.createLoop(2);
    	System.out.println(sll1.HasLoop());
    	sll1.OpenLoop();
    	System.out.println(sll1.HasLoop());*/
    	
    	SinglyLinkedList sll2 = new SinglyLinkedList();
    	sll2.addNode(6);
    	sll2.addNode(7);
    	sll2.addNode(8);
    	
    	CreateIntersecedLists(sll1, sll2);
    	sll2.display();
    	sll1.display();

    	System.out.println(hasIntersection(sll1, sll2));
    	seperateIntersectedLoops(sll1, sll2);
    	System.out.println(hasIntersection(sll1, sll2));    	
    }
}
