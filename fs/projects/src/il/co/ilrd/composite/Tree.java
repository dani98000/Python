package il.co.ilrd.composite;

import java.io.File;
import java.io.FileNotFoundException;

public class Tree {
	private Branch b;

	public Tree(String path) throws FileNotFoundException {
		File file = new File(path);
		if(!file.exists()) {
			throw new FileNotFoundException();
		}
		b = new Branch(file);
	}
	
	public void printTree() {
		b.print();
	}
}
