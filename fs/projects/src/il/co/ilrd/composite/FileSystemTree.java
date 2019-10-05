package il.co.ilrd.composite;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.List;
import java.util.function.Function;

import il.co.ilrd.factory.Factory;

public class FileSystemTree {

	private Branch currBranch;
	private Factory<String,String,FileSystemNode> factory = new Factory<>();

	public FileSystemTree(String path) throws FileNotFoundException {
		factory.add("Leaf", (String str)->new Leaf(str).apply(str));
		factory.add("Branch", (String str)->new Branch(str).apply(str));

		File file = new File(path);
		if(!file.exists()) {
			throw new FileNotFoundException();
		}
		currBranch = (Branch) factory.create("Branch",path);
	}
	
	public void print() {
		System.out.println(ANSI_RED + "hey" + ANSI_RESET);
		currBranch.print();
	}
	
	private interface FileSystemNode extends Function<String,FileSystemNode>{
		public void print();
	}
	
	private class Branch implements FileSystemNode{
		private List<FileSystemNode> trees = new ArrayList<>();
		File dir;
		
		public Branch(String dirName) {
			this.dir = new File(dirName);
			trees = CreateList();
		}
		
		public List<FileSystemNode> CreateList() {
			File[] listOfFiles = dir.listFiles();

			for(File currFile : listOfFiles) {
				if (currFile.isFile()) {
					trees.add(factory.create("Leaf",currFile.getName()));
				}else if (currFile.isDirectory()) {
					Branch curr = (Branch) factory.create("Branch",currFile.getAbsolutePath());
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

		@Override
		public FileSystemNode apply(String str) {
			return new Branch(str);
		}
	}
	
	private class Leaf implements FileSystemNode {
		File file;
		
		public Leaf(String fileName) {
			this.file = new File(fileName);
		}
		
		@Override
		public void print() {
			System.out.println(file.getName());
		}

		@Override
		public FileSystemNode apply(String str) {
			return new Leaf(str);
		}
	}
}
