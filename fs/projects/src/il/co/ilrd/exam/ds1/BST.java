package il.co.ilrd.exam.ds1;

import java.util.LinkedList;
import java.util.Queue;

class BST { 
	  
    /* Class containing left and right child of current node and key value*/
    class Node { 
        int key; 
        Node left, right; 
  
        public Node(int item) { 
            key = item; 
            left = right = null; 
        } 
    } 
  
    // Root of BST 
    Node root; 
  
    // Constructor 
    BST() {  
        root = null;  
    } 
  
    // This method mainly calls insertRec() 
    void insert(int key) { 
       root = insertRec(root, key); 
    } 
      
    /* A recursive function to insert a new key in BST */
    Node insertRec(Node root, int key) { 
  
        /* If the tree is empty, return a new node */
        if (root == null) { 
            root = new Node(key); 
            return root; 
        } 
  
        /* Otherwise, recur down the tree */
        if (key < root.key) 
            root.left = insertRec(root.left, key); 
        else if (key > root.key) 
            root.right = insertRec(root.right, key); 
  
        /* return the (unchanged) node pointer */
        return root; 
    } 
  
    // This method mainly calls InorderRec() 
    void inorder()  { 
       inorderRec(root); 
    } 
  
    // A utility function to do inorder traversal of BST 
    void inorderRec(Node root) { 
        if (root != null) { 
            inorderRec(root.left); 
            System.out.println(root.key); 
            inorderRec(root.right); 
        } 
    }
    
    public void ReverseTravRec(Node root) {
    	if(root == null) {
    		return;
    	}
    	ReverseTravRec(root.left);
    	ReverseTravRec(root.right);
    	System.out.println(root.key);
    }
    
    public void reverseLevelOrder(){
    	ReverseTravRec(root);
    }
    
    public void printLevelOrder(){
    	Queue<Node> queue = new LinkedList<>();
    	queue.add(root);
    	
    	while(!queue.isEmpty()) {
    		Node temp = queue.poll();
    		System.out.println(temp.key);
    		
    		if(temp.left != null) {
    			queue.add(temp.left);
    		}
    		
    		if(temp.right != null) {
    			queue.add(temp.right);
    		}
    	}
    }
}
	  