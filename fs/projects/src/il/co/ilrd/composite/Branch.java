package il.co.ilrd.composite;

import java.io.File;
import java.util.ArrayList;
import java.util.List;

public class Branch implements FSNode{
	private List<FSNode> tl = new ArrayList<>();
	File dir;
	
	public Branch(File dir) {
		this.dir = dir;
		tl = CreateList();
	}
	
	public List<FSNode> CreateList() {
		File[] listOfFiles = dir.listFiles();

		for(File currFile : listOfFiles) {
			if (currFile.isFile()) {
				tl.add(new Leaf(currFile));
			}else if (currFile.isDirectory()) {
				Branch curr = new Branch(currFile);
				tl.add(curr);
			}
		}
				
		return tl;
	}
	
	public void print() {
		System.out.println(dir.getAbsolutePath());
		for(FSNode node : tl) {			
			node.print();
		}
	}
}