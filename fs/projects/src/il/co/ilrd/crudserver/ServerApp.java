package il.co.ilrd.crudserver;

import java.io.IOException;
import java.net.SocketException;

import il.co.ilrd.logmonitor.CrudFile;

public class ServerApp {
	public static void main(String[] args) throws IOException, InterruptedException {
		int port = 1234;
		String ip = "localhost";
		CrudFile crudFile = new CrudFile("Hey");
		
		ServerProtocol protocol = new UDPServerProtocol(ip, port);
		Server server = new Server(protocol);
		server.registerNewMessage((data)->{
			crudFile.create(new String(data).trim());
		});
		server.start();
	}
}
