package il.co.ilrd.logmonitor;

import java.io.IOException;
import java.io.RandomAccessFile;
import java.nio.file.*;
import java.util.ArrayList;
import java.util.List;
import java.util.function.Consumer;

public class LogMonitor{
    private final List<Consumer<Exception>> exceptionHandlers = new ArrayList<>();
    private final List<Consumer<String>> eventHandlers = new ArrayList<>();
	private final Path logFilePath;
	private WatchService logWatcher;
	private Thread monitorThread;	
	boolean isStarted = false;
	
	public LogMonitor(String logFileName) {
		logFilePath = Paths.get(logFileName);
		if (!logFilePath.toFile().exists()) {
			throw new IllegalArgumentException();
		}
	}
	
	public void start() throws IOException {
		if(isStarted) { throw new IllegalStateException(); }
		isStarted = true;
		logWatcher = FileSystems.getDefault().newWatchService();
		logFilePath.getParent().register(logWatcher, StandardWatchEventKinds.ENTRY_MODIFY);
		monitorThread = new MonitorThread();
		monitorThread.start();
	}
	
    public void registerEventHandler(Consumer<String> onEnvent) {
    	eventHandlers.add(onEnvent);
    }
    
    public void registerExceptionHandler(Consumer<Exception> onException) {
    	exceptionHandlers.add(onException);
    }
	
	public void stop() throws IOException, InterruptedException {
		if (isStarted = false) { throw new IllegalStateException(); }
		logWatcher.close();
		monitorThread.join();
		isStarted = false;
	}
		
	private class MonitorThread extends Thread {
		private long currentOffset = logFilePath.toFile().length();

		@Override
		public void run() {
			while(true) {
				try {
					WatchKey wk = logWatcher.take();
			        for (WatchEvent<?> event : wk.pollEvents()) {
			            final Path changed = (Path) event.context();
			            if (logFilePath.endsWith(changed)) {
			            	updateFile();
			            }
			        }
			        wk.reset();

				}catch (InterruptedException e) {
					return;
				}catch (ClosedWatchServiceException c) {
					return;
				}
			}
		}
		
		public void updateFile() {
			String line = null;
			
			try (RandomAccessFile raf = new RandomAccessFile(logFilePath.toFile(),"r")){
				for (Consumer<String> eventHandler : eventHandlers) {
					raf.seek(currentOffset);
					while ((line = raf.readLine()) != null){
						eventHandler.accept(line + System.lineSeparator());
					}
				}
			}catch (IOException e) {
				for (Consumer<Exception> exceptionHandler : exceptionHandlers) {
					exceptionHandler.accept(e);
				}
			}
			
			currentOffset = logFilePath.toFile().length();
		}
	}
}
