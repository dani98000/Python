package chatroomV2;

import java.io.IOException;
import java.net.InetSocketAddress;
import java.net.SocketAddress;
import java.nio.ByteBuffer;
import java.nio.channels.SelectionKey;
import java.nio.channels.Selector;
import java.nio.channels.ServerSocketChannel;
import java.nio.channels.SocketChannel;
import java.util.Iterator;
import java.util.Set;
import java.util.function.BiConsumer;
import java.util.function.Consumer;

public class TCPServer implements Server<Client>{
	private SocketAddress socketAddress;
    private ByteBuffer buffer = ByteBuffer.allocate(256);
	private ServerSocketChannel serverSocket;
	private Selector selector;
	private Consumer<Client> onNewClient;
	private BiConsumer<Client , String> onNewMessage;
	private Consumer<Client> onClientDisconnect;
	
	public TCPServer(String ip, int port) {
		try {
			socketAddress = new InetSocketAddress(ip,port);
			initiateServer();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
	
	private void initiateServer() throws IOException {
		selector = Selector.open();
    	serverSocket = ServerSocketChannel.open();
    	serverSocket.bind(socketAddress);
		serverSocket.configureBlocking(false);
		serverSocket.register(selector, SelectionKey.OP_ACCEPT);
	}
	
	public void start() throws IOException {
    	 while (true) {
         	selector.select();
         	Iterator<SelectionKey> iter = selector.selectedKeys().iterator();
         	
         	while(iter.hasNext()) {
         		SelectionKey key = iter.next();
         		iter.remove();
         		
         		if(key.isAcceptable()) {
         			handleAccept(key);
         		}
         		else if(key.isReadable()) {
         			handleRead(key);
         		}
         		
         		if(!key.isValid()) {
         			onClientDisconnect.accept((Client)key.attachment());
         		}
         	}
    	 }
    }
	
	private void handleRead(SelectionKey key) throws IOException {
		SocketChannel client = ((SocketChannel) key.channel());
		int bytesRead;
		buffer.clear();
		
		while (0 != (bytesRead = client.read(buffer))) {
			if (-1 == bytesRead) {
				key.cancel();
				
				return;
			}
			
			if (0 == buffer.remaining()) {
				ByteBuffer biggerBuf = ByteBuffer.allocate(buffer.capacity() * 2);
				biggerBuf.put(buffer.array());
				buffer = biggerBuf;
			}
		}
		
		System.out.println(new String(buffer.array()));
		buffer.flip();
		String msg = MessageDecoder.decodeMessage(buffer);

		onNewMessage.accept((Client)key.attachment() ,msg);
	}	
	
	public void handleAccept(SelectionKey key) throws IOException {
		SocketChannel clientSocket = ((ServerSocketChannel)key.channel()).accept();
		clientSocket.configureBlocking(false);
		SelectionKey clientKey = clientSocket.register(selector, SelectionKey.OP_READ);
		ClientImpl client = new ClientImpl(clientSocket);
		clientKey.attach(client);
		onNewClient.accept(client);
	}
	
	@Override
	public void registerNewClient(Consumer<Client> onNewClient) {
		this.onNewClient = onNewClient;
	}

	@Override
	public void registerNewMessage(BiConsumer<Client ,String> onNewMessage) {
		this.onNewMessage = onNewMessage;
	}

	@Override
	public void registerClientDisconnect(Consumer<Client> onClientDisconnect) {
		this.onClientDisconnect = onClientDisconnect;	
	}
	
	private class ClientImpl implements Client{
		private SocketChannel client;
		
		public ClientImpl(SocketChannel client) {
			this.client = client;
		}
		
		@Override
		public void sendMessage(String message) {	
			try {
				client.write(MessageDecoder.encodeMessage(message));
			} catch (IOException e) {
				e.printStackTrace();
			}
		}
	}
}