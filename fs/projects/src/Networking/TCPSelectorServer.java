package Networking;

import java.io.IOException;
import java.net.InetSocketAddress;
import java.nio.ByteBuffer;
import java.nio.channels.SelectionKey;
import java.nio.channels.Selector;
import java.nio.channels.ServerSocketChannel;
import java.nio.channels.SocketChannel;
import java.util.Iterator;
import java.util.Set;

public class TCPSelectorServer {
	public static void main(String[] args) throws IOException, InterruptedException {
	    Selector selector = Selector.open();
        ServerSocketChannel serverSocket = ServerSocketChannel.open();
        serverSocket.bind(new InetSocketAddress("localhost", 5454));
        serverSocket.configureBlocking(false);
        serverSocket.register(selector, SelectionKey.OP_ACCEPT);
        ByteBuffer buffer = ByteBuffer.allocate(256);
 
        while (true) {
            selector.select();
            Set<SelectionKey> selectedKeys = selector.selectedKeys();
            Iterator<SelectionKey> iter = selectedKeys.iterator();
            while (iter.hasNext()) {
                SelectionKey key = iter.next();
 
                if (key.isAcceptable()) {
                    register(selector, serverSocket);
                }
 
                if (key.isReadable()) {
                    answerWithEcho(buffer, key);
                }
                iter.remove();
            }
        }
	}
	
	 private static void answerWithEcho(ByteBuffer buffer, SelectionKey key)
		      throws IOException, InterruptedException {
		  
		        SocketChannel client = (SocketChannel) key.channel();
		        client.read(buffer);
		        Thread.sleep(1000);
		        //System.out.println(new String(buffer.array(), "ASCII"));
		        System.out.println(new String(buffer.array()));
		        String msg = "Pong";
		        client.write(ByteBuffer.wrap(msg.getBytes()));
		        buffer.clear();
		    }
		 
		    private static void register(Selector selector, ServerSocketChannel serverSocket)
		      throws IOException {
		  
		        SocketChannel client = serverSocket.accept();
		        client.configureBlocking(false);
		        client.register(selector, SelectionKey.OP_READ);
		    }
}
