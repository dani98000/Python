package il.co.ilrd.jarloader;

import java.io.IOException;

public class Main {
	public static void main(String[] args) throws Exception {
		JarRunner runner= new JarRunner("/home/dani98000/daniel-maizel/fs/projects/src/il/co/ilrd/jarexercise/MyJarFile.jar" ,"Person");
		runner.dynamicallyLoadClasses();
	}
}
