package il.co.ilrd.test;

import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class Test {
	static class Node 
	{ 
	    int data; 
	    Node left, right; 
	    
	    public Node(int item) 
	    { 
	        data = item; 
	        left = right = null; 
	    } 
	} 
	  
	static class BinaryTree 
	{ 
	    Node root; 
	  
	    public BinaryTree() 
	    { 
	        root = null; 
	    } 
	    
	    public int getHeight(Node root) {
	    	if(root == null) {
	    		return 0;
	    	}
	    	
	    	int leftChild = getHeight(root.left);
	    	int rightChild = getHeight(root.left);
	    	
	    	return leftChild > rightChild ? leftChild + 1 : rightChild + 1;
	    }
	    
	    public void printGivenLevel(Node root, int level) {
	    	if(root == null) {
	    		return;
	    	}
	    	if(level == 1) {
	    		System.out.print(root.data + " ");
	    	}else if(level > 1) {
	    		printGivenLevel(root.left, level - 1);
	    		printGivenLevel(root.right, level - 1);
	    	}
	    	
	    }
	    
	    public void printLevelTraversal() {
	    	int h = getHeight(root);	  
	    	
	    	for (int i = 1; i <= h; i++) {
	    		printGivenLevel(root, i);
	    		System.out.println();
			}
	    }
	}
	
	public static void main(String[] args) {
		BinaryTree tree = new BinaryTree(); 
	    tree.root= new Node(1); 
	    tree.root.left= new Node(2); 
	    tree.root.right= new Node(3); 
	    tree.root.left.left= new Node(4); 
        tree.root.left.right= new Node(5); 
        
        tree.printLevelTraversal();
	}
}

