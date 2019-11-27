package il.co.ilrd.helloworld;

import java.io.IOException;
import il.co.ilrd.logmonitor.LogMonitor;
import il.co.ilrd.networking.ClientLogProtocol;
import il.co.ilrd.networking.ClientProtocol;
import il.co.ilrd.networking.HTTPClientAdapter;

public class HttpClientTest {
	public static void main(String[] args) throws IOException {
		String fileToMonitor = "/home/dani98000/daniel-maizel/fs/projects/textToLog";
		LogMonitor monitor = new LogMonitor(fileToMonitor);
		ClientProtocol protocol = new ClientLogProtocol(new HTTPClientAdapter());
		
		monitor.registerEventHandler((String update) -> {
			try {
				System.out.println("[Client] sending: " + update + " to server...");
				protocol.SendData(update.getBytes());
				System.out.println("[Client] update acknowledged!");
			} catch (IOException e) {
				e.printStackTrace();
			}
		});
		
		monitor.start();
	}
}
