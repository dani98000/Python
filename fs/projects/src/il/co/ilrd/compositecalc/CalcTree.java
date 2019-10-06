package il.co.ilrd.compositecalc;

import java.util.LinkedList;
import java.util.TreeMap;

import il.co.ilrd.compositecalc.BST.Node;

public class CalcTree {
	BST tree = new BST();
	Node root = tree.root;
	
	
	private final static int LEFT = 1;
	private final static int RIGHT = 2;
	
	public CalcTree() {
		Node curr = tree.insert('+',LEFT, null);
		tree.insert('3',LEFT,curr);
		Node temp = tree.insert('*',RIGHT,curr);
		Node temp2 = tree.insert('+',LEFT,temp);
		tree.insert('2',RIGHT,temp);
		tree.insert('5', LEFT, temp2);
		tree.insert('9', RIGHT, temp2);
	}
	
	public interface Calculatable {int calculate();}
	
	public class Leaf implements Calculatable{
		char key;
		public Leaf(char key) {
			this.key = key;
		}
		@Override
		public int calculate() {
			return Character.getNumericValue(key);
		}
	}
	
	public class Tree implements Calculatable{
		Calculatable operator;
		Calculatable left, right;
		char key;
		
		public Tree(char key) {
			this.key = key;
		}
		@Override
		public int calculate() {
			switch(operator.key) {
				case('+'):
					return Character.getNumericValue(operator.left.key) + Character.getNumericValue(operator.right.key);
				case('-'):
					return Character.getNumericValue(operator.left.key) - Character.getNumericValue(operator.right.key);
				case('*'):
					return Character.getNumericValue(operator.left.key) * Character.getNumericValue(operator.right.key);
				case('/'):
					return Character.getNumericValue(operator.left.key) / Character.getNumericValue(operator.right.key);
			}
			
			return 0;
		}
	}
	
	public static void main(String[] args) {
		BST tree = new BST();

	}
}
