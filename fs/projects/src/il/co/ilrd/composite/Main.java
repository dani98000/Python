package il.co.ilrd.composite;

import java.io.FileNotFoundException;

public class Main {
	public static void main(String[] args) throws FileNotFoundException {
		FileSystemTree tree = new FileSystemTree("/home/ol69/daniel-maizel");
		tree.print();
	}
}
