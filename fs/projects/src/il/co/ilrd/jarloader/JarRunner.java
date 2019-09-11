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


public class JarRunner {
		private URL url;
		private String interfaceName;
		private List<String> classesToLoad;
		private JarClassLoader cl;
		
		public JarRunner(String pathName, String interfaceName) throws IOException{
			url = new File(pathName).toURI().toURL();
			this.interfaceName = interfaceName;			
			cl = new JarClassLoader(url);
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
		private URL jarUrl;
		
		public JarClassLoader(URL url) {
			super(new URL[] { url });
			this.jarUrl = url;
		}
		
		public List<String> getClassList() throws IOException{
			URL u = new URL("jar", "", jarUrl + "!/");
			
		    JarURLConnection uc = null;
			uc = (JarURLConnection)u.openConnection();
	

			List<String> classes = new ArrayList<>();
			Enumeration<JarEntry> entries = null;
			entries = uc.getJarFile().entries();
			
			while(entries.hasMoreElements()) {
				Object obj = entries.nextElement();
				if(obj.toString().endsWith(".class")) {
					classes.add(obj.toString() .replaceAll(".class","").replaceAll("/", "."));
				}
			}
		    return classes;
		}
	}
}
