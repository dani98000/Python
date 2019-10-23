package logmonitor;

import java.io.FileNotFoundException;
import java.io.IOException;

public class Main {
	public static void main(String[] args) throws InterruptedException, FileNotFoundException, IOException {
		LogMonitor monitor = new LogMonitor();
		monitor.watch();		
	}
}
