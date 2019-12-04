package il.co.ilrd.logmonitor;

import java.io.IOException;
import java.net.SocketException;

import il.co.ilrd.logmonitor.LogMonitor;
import il.co.ilrd.networking.ClientProtocol;
import il.co.ilrd.networking.ClientLogProtocol;

public class LogClient {
	public static void main(String[] args) throws IOException {
		int port = 1234;
		String ip = "localhost";
		String fileToMonitor = "/home/dani98000/daniel-maizel/fs/projects/textToLog";
		LogMonitor monitor = new LogMonitor(fileToMonitor);
		ClientProtocol protocol = new ClientLogProtocol(ip, port);
		
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
