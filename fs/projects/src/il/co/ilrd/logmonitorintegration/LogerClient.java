package il.co.ilrd.logmonitorintegration;

import java.io.IOException;
import java.net.InetSocketAddress;
import java.net.SocketAddress;
import java.net.SocketException;

import il.co.ilrd.logmonitor.LogMonitor;

public class LogerClient {
	public static void main(String[] args) throws IOException, InterruptedException {
		String fileToMonitor = "/home/dani98000/daniel-maizel/fs/projects/textToLog";
		int port = 1234;
		String ip = "localhost";
		SocketAddress remoteAddress = new InetSocketAddress(ip, port);
		LogMonitor monitor = new LogMonitor(fileToMonitor);
		UDPLogProtocol protocol= new UDPLogProtocol(null, remoteAddress);
		monitor.registerEventHandler((String update) -> {
			try {
				System.out.println("[Client] sending: " + update + " to server...");
				protocol.send(update);
				System.out.println("[Client] update acknowledged!");
			} catch (IOException e) {
				e.printStackTrace();
			}
		});
		
		monitor.start();
	}
}
