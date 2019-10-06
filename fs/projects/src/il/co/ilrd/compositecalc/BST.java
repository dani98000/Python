package il.co.ilrd.compositecalc;

import java.util.LinkedList;
import java.util.Queue;

import il.co.ilrd.compositecalc.CalcTree.Calculatable;
import il.co.ilrd.compositecalc.CalcTree.Tree;

public class BST { 
	  
    /* Class containing left and right child of current node and key value*/

    // Root of BST 
	Calculatable root; 
  
    // Constructor 
    public BST() {  
        root = null;  
    } 
  
    Calculatable insert(char key, int side, Calculatable newRoot, int leafOrTree) { 
    	if(newRoot == null) {
    		newRoot = new Tree(key);
    		root = newRoot;
    	}else {	
	        if(side == 1) {
	        	if(leafOrTree == 1) {
	        		newRoot.left = new Tree(key);	        		
	        	}else {
	        		newRoot.left = new Leaf(key);	        		
	        	}
	     	   
	     	   return root.left;
	        }else {
	        	newRoot.right = new Node(key);
	    	   
	    	   return newRoot.right;
	        }
    	}
	       
        return newRoot;
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