package Networking;

import java.io.IOException;
import java.net.InetSocketAddress;
import java.nio.channels.Selector;
import java.nio.channels.ServerSocketChannel;

public class NIOServer {
		public static void main(String[] args) throws IOException {
			Selector selector = Selector.open();
			ServerSocketChannel serverSocketChannel = ServerSocketChannel.open();
			InetSocketAddress inetAddr = new InetSocketAddress("local host", 1111);
			serverSocketChannel.bind(inetAddr);
			serverSocketChannel.regis
			
		}
}
