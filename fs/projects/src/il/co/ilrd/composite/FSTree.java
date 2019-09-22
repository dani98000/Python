package il.co.ilrd.composite;

import java.io.File;
import java.io.FileNotFoundException;

public class FSTree {
	private Branch currBranch;

	public FSTree(String path) throws FileNotFoundException {
		File file = new File(path);
		if(!file.exists()) {
			throw new FileNotFoundException();
		}
		currBranch = new Branch(file);
	}
	
	public void print() {
		currBranch.print();
	}
}
