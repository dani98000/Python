package il.co.ilrd.gateway;

import java.io.IOException;
import java.net.InetSocketAddress;

import com.sun.net.httpserver.HttpServer;

public class GatewayServer {
	public static void main(String[] args) throws IOException {
		HttpServer server = HttpServer.create(new InetSocketAddress("localhost", 5555), 0);
		HttpRequestHandler handler = new HttpRequestHandler(server);
		server.start();
	}
}