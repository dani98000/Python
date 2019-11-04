package chatroom;

import java.io.BufferedReader;
import java.io.Closeable;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.InetAddress;
import java.net.InetSocketAddress;
import java.net.ServerSocket;
import java.nio.ByteBuffer;
import java.nio.channels.SelectionKey;
import java.nio.channels.Selector;
import java.nio.channels.ServerSocketChannel;
import java.nio.channels.SocketChannel;
import java.util.Iterator;
import java.util.Set;

public class ServerSide implements Closeable{
	private final int port;
	private ServerSocketChannel serverSocket;
	private Selector selector;
    ByteBuffer buffer = ByteBuffer.allocate(256);
	//private final ByteBuffer welcomeBuf = ByteBuffer.wrap("Welcome to my chat! Please enter your name.\n".getBytes());

    public ServerSide(int port) throws IOException {
    	this.port = port;
    	selector = Selector.open();
    	serverSocket = ServerSocketChannel.open();
    	serverSocket.bind(new InetSocketAddress("localhost" ,port));
		serverSocket.configureBlocking(false);
		serverSocket.register(selector, SelectionKey.OP_ACCEPT);
    }
    
    public void start() throws IOException {
    	 while (true) {
         	selector.select();
         	Set<SelectionKey> selectedKeys = selector.selectedKeys();
         	Iterator<SelectionKey> iter = selectedKeys.iterator();
         	
         	while(iter.hasNext()) {
         		SelectionKey key = iter.next();
         		iter.remove();
         		
         		if(key.isAcceptable()) {
         			handleAccept(key);
         		}
         		
         		if(key.isReadable()) {
         			if(null == key.attachment()) {
         				registerNewUser(key);
         			}else {
         				handleRead(key);
         			}
         		}
         	}
    	 }
    }
	
	private void handleRead(SelectionKey key) throws IOException {
		SocketChannel client = (SocketChannel) key.channel();
		StringBuilder sb = new StringBuilder();

		buffer.clear();
		int read = 0;
		
		while( (read = client.read(buffer)) > 0 ) {
			buffer.flip();
			byte[] bytes = new byte[buffer.limit()];
			buffer.get(bytes);
			sb.append(new String(bytes));
			buffer.clear();
		}
		
		String msg;
		if(read < 0) {
			msg = key.attachment() + " left the chat.\n";
			client.close();
		}
		else {
			msg = key.attachment() + ": " + sb.toString();
		}

		ByteBuffer msgBuf = ByteBuffer.wrap(msg.getBytes());
		for(SelectionKey currentKey : selector.keys()) {
			if(currentKey.isValid() && currentKey.channel() instanceof SocketChannel
				&& currentKey.channel() != client) {
				SocketChannel sch = (SocketChannel) currentKey.channel();
				sch.write(msgBuf);
				msgBuf.rewind();
			}
		}
	}	
	
	public void handleAccept(SelectionKey key) throws IOException {
		SocketChannel client = ((ServerSocketChannel) key.channel()).accept();
		String address =client.getRemoteAddress() + ":" + client.socket().getPort();
		client.configureBlocking(false);
		client.register(selector, SelectionKey.OP_READ);
		client.write(ByteBuffer.wrap("Hey Please enter your name:".getBytes()));
	}
	
	public void registerNewUser(SelectionKey key) throws IOException {
		StringBuilder sb = new StringBuilder();
		SocketChannel client = ((SocketChannel) key.channel());

		buffer.clear();
		int read = 0;
		while((read = client.read(buffer)) > 0 ) {
			buffer.flip();
			byte[] bytes = new byte[buffer.limit()];
			buffer.get(bytes);
			sb.append(new String(bytes));
			buffer.clear();
		}		
		
		String clientName = sb.toString();
		key.attach(clientName);
		client.write(ByteBuffer.wrap(("Welcome to my chat," + key.attachment()).getBytes()));
		System.out.println("accepted connection from: " + clientName);		
	}
	
	public static void main(String[] args) throws IOException, InterruptedException {
		ServerSide server = new ServerSide(8080);
		server.start();
	}

	@Override
	public void close() throws IOException {
		Set<SelectionKey> selectedKeys = selector.selectedKeys();
     	Iterator<SelectionKey> iter = selectedKeys.iterator();
     	
     	while(iter.hasNext()) {
     		SelectionKey key = iter.next();
    		SocketChannel client = (SocketChannel) key.channel();
    		client.close();
     		iter.remove();
     	}
     	
     	selector.close();
	}
}