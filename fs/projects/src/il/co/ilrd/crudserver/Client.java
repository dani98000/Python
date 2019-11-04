package il.co.ilrd.crudserver;

import java.io.IOException;
import java.net.SocketException;

import il.co.ilrd.logmonitor.LogMonitor;

public class Client {
	public static void main(String[] args) throws IOException {
		int port = 1234;
		String ip = "localhost";
		String fileToMonitor = "/home/dani98000/daniel-maizel/fs/projects/textToLog";

		
		LogMonitor monitor = new LogMonitor(fileToMonitor);
		UDPClientProtocol protocol = new UDPClientProtocol(ip, port);
		
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
