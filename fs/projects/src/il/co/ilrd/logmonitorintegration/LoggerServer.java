package il.co.ilrd.logmonitorintegration;

import java.io.IOException;
import java.net.InetSocketAddress;

import il.co.ilrd.logmonitor.CrudFile;

public class LoggerServer {
	Protocol<String> protocol;
	CrudFile crudFile;
	
	public LoggerServer(Protocol<String> protocol, String crudFile) throws IOException {
		this.protocol = protocol;
		this.crudFile = new CrudFile(crudFile);
	}
	
	public void start() {
		System.out.println("[Server] server running...");
		System.out.println();
		while(true) {
			try {
				String newData = protocol.receive();
				crudFile.create(newData);
				System.out.println("[Server] got update: " + newData);
			} catch (IOException e) {
				System.out.println("Problum Occured, didnt receive the new Data");
			}
		}
	}
	
	public static void main(String[] args) throws IOException {
		String crudFileName = "testing";
		String ip = "localhost";
		int port = 1234;
		InetSocketAddress bindAddress = new InetSocketAddress(ip,port);
		Protocol<String> protocol = new UDPLogProtocol(bindAddress);
		LoggerServer server = new LoggerServer(protocol, crudFileName);
		server.start();
	}
}
