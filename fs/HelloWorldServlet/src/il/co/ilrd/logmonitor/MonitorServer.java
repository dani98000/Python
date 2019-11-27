package il.co.ilrd.logmonitor;

import java.io.IOException;
import java.net.SocketException;

import il.co.ilrd.logmonitor.CrudFile;
import il.co.ilrd.networking.Server;
import il.co.ilrd.networking.ServerLogProtocol;
import il.co.ilrd.networking.ServerProtocol;

public class MonitorServer {
	public static void main(String[] args) throws IOException {
		int port = 1234;
		String ip = "localhost";
		CrudFile crudFile = new CrudFile("Hey");	
		ServerProtocol protocol = null;
	
		try {
			protocol = new ServerLogProtocol(ip, port);
		} catch (SocketException e) {
			e.printStackTrace();
		}
		
		Server server = new Server(protocol);
		
		server.registerNewMessage((data)->{
			crudFile.create(new String(data).trim());
		});
		
		server.start();
	}
}
