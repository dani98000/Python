package logmonitor;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.nio.file.FileSystems;
import java.nio.file.Path;
import java.nio.file.StandardWatchEventKinds;
import java.nio.file.WatchEvent;
import java.nio.file.WatchKey;
import java.nio.file.WatchService;

import il.co.ilrd.crud.Crud;

public class LogMonitor{
	private static final String logName = "logcopy";
	private static final String logPath = "/var/log";
	private static final String fullPath = "/var/log/syslog";
	private Path log;
	private WatchService logWatcher;
	private Crud<String, Integer> crudFile = new CrudFile(logName);
	
	public LogMonitor(){
		log = FileSystems.getDefault().getPath(logPath);
		try {
			logWatcher = log.getFileSystem().newWatchService();
			log.register(logWatcher, StandardWatchEventKinds.ENTRY_MODIFY);
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
	
	public void watch() throws InterruptedException, FileNotFoundException, IOException {
    	BufferedReader br = new BufferedReader(new FileReader(new File(fullPath)));
    	String s;
    	int counter = 0;
	    while((s = br.readLine()) != null){
	    	crudFile.Create(s + "\n");
	    	++counter;
	    } 
	    
		while(true) {
	        final WatchKey wk = logWatcher.take();
	        for (WatchEvent<?> event : wk.pollEvents()) {
	            final Path changed = (Path) event.context();
	            if (changed.endsWith("syslog")) {
	                System.out.println("My file has changed");
	                br = new BufferedReader(new FileReader(new File(fullPath)));
	                int i = 0;
	        	    while((s = br.readLine()) != null){
	        	    	++i;
	        	    	if(i >= counter) {
		        	    	crudFile.Create(s + "\n");
		        	    	++counter;
	        	    	}
	        	    } 
	            }
	        }
	        // reset the key
	        boolean valid = wk.reset();
	        if (!valid) {
	            System.out.println("Key has been unregistered");
	        }
	    }
	}
}
