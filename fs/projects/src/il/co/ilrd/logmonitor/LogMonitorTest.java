package il.co.ilrd.logmonitor;

import static org.junit.jupiter.api.Assertions.*;

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.io.RandomAccessFile;
import java.util.function.Consumer;

import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.Test;

class LogMonitorTest {	

	@Test
	void test() {
		try (CrudFile crudFile = new CrudFile("testlogcopy2")) {
			Consumer<String> consumer = (String text) -> crudFile.create(text);
			File textToLog = new File("/home/dani98000/daniel-maizel/fs/projects/textToLog");
			if(!textToLog.exists()) {
				textToLog.createNewFile();
			}
			LogMonitor monitor = new LogMonitor("/home/dani98000/daniel-maizel/fs/projects/textToLog");
			monitor.registerEventHandler(consumer);
			monitor.start();
			
			RandomAccessFile raf = new RandomAccessFile(new File("testlogcopy2"), "r");
		    BufferedWriter writer = new BufferedWriter(new FileWriter(textToLog,true));
		     		
			writer.write("Daniel" + System.lineSeparator());
			writer.close();
			Assertions.assertEquals(raf.readLine(),"Daniel");
			textToLog.delete();
			monitor.stop();
		} catch (IOException e) {
			System.out.println("reached1");
		} catch (Exception e) {
			System.out.println("reached2");
		}
	}
}
