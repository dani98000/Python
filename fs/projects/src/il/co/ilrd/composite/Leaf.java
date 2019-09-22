package il.co.ilrd.composite;

import java.io.File;

public class Leaf implements FSNode{
	File file;
	
	public Leaf(File file){
		this.file = file;
	}
	
	@Override
	public void print() {
		System.out.println(file.getName());
	}
}
