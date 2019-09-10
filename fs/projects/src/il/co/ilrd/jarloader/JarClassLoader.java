package il.co.ilrd.jarloader;

import java.io.IOException;
import java.lang.reflect.Constructor;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.lang.reflect.Modifier;
import java.net.JarURLConnection;
import java.net.MalformedURLException;
import java.net.URL;
import java.net.URLClassLoader;
import java.util.ArrayList;
import java.util.Enumeration;
import java.util.List;
import java.util.jar.Attributes;
import java.util.jar.JarEntry;
import java.util.jar.JarFile;
import java.util.zip.ZipEntry;
import java.net.JarURLConnection;

public class JarClassLoader extends URLClassLoader{
	URL url;
	
	public JarClassLoader(URL url) {
		super(new URL[] { url });
		this.url = url;
	}
	
	public List<String> getClassList(){
		URL u = null;
		try {
			u = new URL("jar", "", url + "!/");
		} catch (MalformedURLException e) {
			e.printStackTrace();
		}
	    System.out.println(u);
	    JarURLConnection uc = null;
		try {
			uc = (JarURLConnection)u.openConnection();
		} catch (IOException e) {
			e.printStackTrace();
		}

		List<String> classes = new ArrayList<>();
		Enumeration<JarEntry> attr = null;
		try {
			attr = uc.getJarFile().entries();
		} catch (IOException e) {
			e.printStackTrace();
		}
		while(attr.hasMoreElements()) {
			Object obj = attr.nextElement();
			if(obj.toString().endsWith(".class")) {
				classes.add(obj.toString());
			}
		}
	    return classes;
	}
}
