package il.co.ilrd.composite;

import java.io.FileNotFoundException;

public class Main {
	public static void main(String[] args) throws FileNotFoundException {
		Tree tree = new Tree("/home/dani98000/Desktop/");
		tree.printTree();
	}
}
