package logmonitor;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.RandomAccessFile;
import java.nio.file.FileSystems;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.nio.file.StandardWatchEventKinds;
import java.nio.file.WatchEvent;
import java.nio.file.WatchKey;
import java.nio.file.WatchService;

import il.co.ilrd.crud.Crud;

public class LogMonitor{
	private final Path logFilePath;
	private WatchService logWatcher;
	private Crud<String, Integer> crudFile;
	private Thread monitorThread;
	
	public LogMonitor(String logFileName, String crudFileName){
		logFilePath = Paths.get(logFileName);
		crudFile = new CrudFile(crudFileName);
		try {
			logWatcher = FileSystems.getDefault().newWatchService();
			logFilePath.getParent().register(logWatcher, StandardWatchEventKinds.ENTRY_MODIFY);
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
	
	public void start() throws FileNotFoundException {
		monitorThread = new MonitorThread();
		monitorThread.start();
	}
	
	public void stop() throws IOException, InterruptedException {
		try {
			crudFile.close();
		} catch (Exception e) {
			throw new IOException();
		}
		
		logWatcher.close();
		monitorThread.join();
	}
		
	private class MonitorThread extends Thread {
		private long currentOffset = 0;

		@Override
		public void run() {
			updateFile();
	    
			while(true) {
				try {
					WatchKey wk = logWatcher.take();
			        for (WatchEvent<?> event : wk.pollEvents()) {
			            final Path changed = (Path) event.context();
			            if(changed.endsWith("syslog")) {
			            	updateFile();
			            }
			        }
			        // reset the key
			        boolean valid = wk.reset();
			        if (!valid) {
			            System.out.println("Key has been unregistered");
			        }
				}catch(InterruptedException e) {
					e.printStackTrace();
				}
			}
		}
		
		public void updateFile() {
			long offset = currentOffset;
			String line = null;
			try{
				RandomAccessFile raf = new RandomAccessFile(logFilePath.toFile(),"r");
				while((line = raf.readLine()) != null){
					crudFile.Create(line + "\n");
				}				
			}catch(IOException e) {
				e.printStackTrace();
			}

			currentOffset = logFilePath.toFile().length();
		}
	}
}
