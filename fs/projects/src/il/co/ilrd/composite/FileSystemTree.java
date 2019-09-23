package il.co.ilrd.composite;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.List;

public class FileSystemTree {
	private Branch currBranch;

	public FileSystemTree(String path) throws FileNotFoundException {
		File file = new File(path);
		if(!file.exists()) {
			throw new FileNotFoundException();
		}
		currBranch = new Branch(file);
	}
	
	public void print() {
		currBranch.print();
	}
	
	private interface FileSystemNode {
		public void print();
	}
	
	private class Branch implements FileSystemNode{
		private List<FileSystemNode> trees = new ArrayList<>();
		File dir;
		
		public Branch(File dir) {
			this.dir = dir;
			trees = CreateList();
		}
		
		public List<FileSystemNode> CreateList() {
			File[] listOfFiles = dir.listFiles();

			for(File currFile : listOfFiles) {
				if (currFile.isFile()) {
					trees.add(new Leaf(currFile));
				}else if (currFile.isDirectory()) {
					Branch curr = new Branch(currFile);
					trees.add(curr);
				}
			}
					
			return trees;
		}
		
		public void print() {
			System.out.println(dir.getAbsolutePath());
			for (FileSystemNode node : trees) {			
				node.print();
			}
		}
	}
	
	private class Leaf implements FileSystemNode {
		File file;
		
		public Leaf(File file) {
			this.file = file;
		}
		
		@Override
		public void print() {
			System.out.println(file.getName());
		}
	}
}
