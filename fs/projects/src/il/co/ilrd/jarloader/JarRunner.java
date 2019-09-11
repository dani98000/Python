package il.co.ilrd.jarloader;

import java.io.File;
import java.io.IOException;
import java.net.JarURLConnection;
import java.net.URL;
import java.net.URLClassLoader;
import java.util.ArrayList;
import java.util.Enumeration;
import java.util.List;
import java.util.jar.JarEntry;
import java.util.jar.JarFile;


public class JarRunner {
		private String interfaceName;
		private List<String> classesToLoad;
		private JarClassLoader cl;
		private String pathName;
		
		public JarRunner(String pathName, String interfaceName) throws IOException{
			this.interfaceName = interfaceName;	
			this.pathName = pathName;
			cl = new JarClassLoader(new File(pathName).toURI().toURL());
			classesToLoad = cl.getClassList();
		}
	    
		public void dynamicallyLoadClasses() throws Exception {
		    for(String clazz : classesToLoad) {
		    	Class<?>curr = cl.loadClass(clazz);
		    	Class<?>[] interfaces = curr.getInterfaces();
		    	for(Class<?> currInterface : interfaces) {
		    		if(currInterface.getSimpleName().equals(interfaceName)){
			    		System.out.println(curr.getSimpleName());
		    		}
		    	}
			}
		}

	private class JarClassLoader extends URLClassLoader{
		public JarClassLoader(URL url) {
			super(new URL[] { url });
		}
		
		public List<String> getClassList() throws IOException{
			JarFile myFile = new JarFile(pathName);
			List<String> classes = new ArrayList<>();
			Enumeration<JarEntry> entries = myFile.entries();
			
			while(entries.hasMoreElements()) {
				JarEntry obj = entries.nextElement();
				if(obj.getName().endsWith(".class")) {
					classes.add(obj.getName().replaceAll(".class","").replaceAll("/", "."));
				}
			}
			myFile.close();
			
		    return classes;
		}
	}
}