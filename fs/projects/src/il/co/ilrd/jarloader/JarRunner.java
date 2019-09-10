package il.co.ilrd.jarloader;

import java.io.File;
import java.net.MalformedURLException;
import java.net.URL;
import java.util.List;

public class JarRunner {
	public static void main(String[] args) {
	    if (args.length < 1) {
	        System.out.println("Not enough args");
	    }
	    URL url = null;
	    try {
	    	 url = new File(args[0]).toURI().toURL();
	    } catch (MalformedURLException e) {
	        System.out.println("Invalid URL: " + "jar:" + args[0]);
	    }
	    String interfaceName = args[1];
	    
	    JarClassLoader cl = new JarClassLoader(url);

	    List<String> classesToLoad = cl.getClassList();
	    
	    for(String clazz : classesToLoad) {
	    	Class<?> curr = null;
	    	try {
	    		curr = cl.loadClass(clazz.replaceAll(".class","").replaceAll("/", "."));
	    		Class<?>[] interfaces = curr.getInterfaces();
	    		for(Class<?> currInterface : interfaces) {
	    			if(currInterface.getSimpleName().equals(interfaceName));{
	    				System.out.println(curr.getSimpleName());
	    			}
	    		}
			} catch (ClassNotFoundException e) {
				e.printStackTrace();
			}
	    }
	

	}
}
