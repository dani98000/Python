package il.co.ilrd.composite;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.List;
import java.util.function.Function;

import il.co.ilrd.factory.Factory;

public class FSTree {
	private FileSystemNode root;
	private Factory<String,Args,FileSystemNode> factory = new Factory<>();
	public static final String ANSI_RESET = "\u001B[0m";
	public static final String ANSI_GREEN = "\u001B[32m";

	public FSTree(String path) throws FileNotFoundException {
		File rootDir = new File(path);
		factory.add("Leaf", (args)->new Leaf(args.getPath()));
		factory.add("Branch", (args)->new Branch(args.getPath(), args.getChildren(), args.getIndentation()));

		File file = new File(path);
		if(!file.exists()) {
			throw new FileNotFoundException();
		}
		root = createTree(rootDir, 0);
	}
	
	private FileSystemNode createTree(File curDir, int indentation) {
		List<FileSystemNode> children = new ArrayList<FileSystemNode>();
		for(File currFile : curDir.listFiles()) {
			if (currFile.isFile()) {
				children.add(factory.create("Leaf",new Args(currFile.getPath())));
			}else if (currFile.isDirectory()) {
				children.add(createTree(currFile, indentation + 1));
			}
		}
			
		return factory.create("Branch", new Args(curDir.getName(), children, indentation));
	}
	
	public void print() {
		root.print();
	}
	
	private interface FileSystemNode{
		public void print();
	}
	
	private class Branch implements FileSystemNode{
		private List<FileSystemNode> children;
		private String name;
		private int indentation;
		
		public Branch(String dirName, List<FileSystemNode> children, int indentation) {
			name = dirName;
			this.children = children;
			this.indentation = indentation;
		}
		
		public void print() {
			System.out.println(ANSI_GREEN + name + ANSI_RESET);
			for (int i = 0, n = children.size(); i < n; ++i) {
				FileSystemNode child = children.get(i);
				printIndentation(indentation);
				child.print();
			}
		}
		
		private void printIndentation(int indent) {
			for (int i = 0; i < indent; ++i) {
				System.out.print("--");
			}
		}
	}
	
	private class Leaf implements FileSystemNode {
		String name;
		
		public Leaf(String fileName) {
			this.name = fileName;
		}
		
		@Override
		public void print() {
			System.out.println(name);
		}

	}
	
	private static class Args {
		private List<FileSystemNode> children;
		private String path;
		private int indentation;
		
		public Args(String path, List<FileSystemNode> children, int indentation) {
			this.children = children;
			this.path = path;
			this.indentation = indentation;
		}
		
		public Args(String path) {
			this(path, null, 0);
		}

		public List<FileSystemNode> getChildren() {
			return children;
		}
		
		public String getPath() {
			return path;
		}
		
		public int getIndentation() {
			return indentation;
		}
	}
}