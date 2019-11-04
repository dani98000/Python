package codereview;

import java.io.IOException;
import java.net.InetSocketAddress;
import java.nio.ByteBuffer;
import java.nio.channels.SelectionKey;
import java.nio.channels.Selector;
import java.nio.channels.ServerSocketChannel;
import java.nio.channels.SocketChannel;
import java.util.Iterator;
import java.util.Set;
import java.util.function.BiConsumer;
import java.util.function.Consumer;

public class TCPSrever implements ChatSrever {
	private final int portNumber = 7777;
	private Consumer<ComObject> onNewClient;
	private BiConsumer<ComObject, String> onNewMessage;
	private Consumer<ComObject> onNewClientDisconnect;
	private boolean shouldStop = false;
	private Selector selector;
	private Protocol protocol;
	
	@Override
	public void openChatServer() throws IOException{
		protocol = new ChatProtocol();
		selector = Selector.open();
		InetSocketAddress address = new InetSocketAddress(portNumber);
		
		try(ServerSocketChannel socketChannel = ServerSocketChannel.open();) {
			socketChannel.bind(address);
			socketChannel.configureBlocking(false);
			socketChannel.register(selector, SelectionKey.OP_ACCEPT);	
			
			while(!shouldStop) {
				selector.select();
				Set<SelectionKey> selectionKeys = selector.selectedKeys();
				Iterator<SelectionKey> iter = selectionKeys.iterator();

				while (iter.hasNext()) {
					SelectionKey key = iter.next();
					
					if (key.isAcceptable()) {
						processAcceptEvent(key);
					} else if (key.isReadable()) {
						processReadEvent(key);
					} 
					
					iter.remove();
				}
			}
		}
		
		selector.close();
	}
	
	public void processAcceptEvent(SelectionKey key) throws IOException { 
		ServerSocketChannel serverSocket = (ServerSocketChannel)key.channel();
		SocketChannel clientSocket = serverSocket.accept();
		System.out.println("Client connected");
		clientSocket.configureBlocking(false);
		SelectionKey currKey = clientSocket.register(selector, SelectionKey.OP_READ | SelectionKey.OP_WRITE);
		ComObjectTCP comObj = new ComObjectTCP(clientSocket);
		currKey.attach(comObj);
		onNewClient.accept(comObj);
	}
	
	public void processReadEvent(SelectionKey key) throws IOException {
		ByteBuffer buffer = ByteBuffer.allocate(1024);
		SocketChannel clientSocket = (SocketChannel)key.channel();
		int read = clientSocket.read(buffer);
		
		if(-1 == read || 0 == read) {
			onNewClientDisconnect.accept((ComObjectTCP)key.attachment());
			key.cancel();
		} else {
			String data = new String(buffer.array(), 0, read);
			buffer.clear();
			if (protocol.isValid(data)) {
				onNewMessage.accept((ComObjectTCP)key.attachment(), protocol.unwrap(data));							
			} else {
				throw new IllegalArgumentException();
			}
		}
	}
		
	@Override
	public void closeChatServer() {
		shouldStop = true;
	}
	
	@Override
	public void registerNewClientMethod(Consumer<ComObject> onNewClient) {
		this.onNewClient = onNewClient;
	}

	@Override
	public void registerMessageMethod(BiConsumer<ComObject, String> onNewMessage) {
		this.onNewMessage = onNewMessage;
	}

	@Override
	public void RegisterClientDisconnectMethod(Consumer<ComObject> onNewClientDisconnect) {
		this.onNewClientDisconnect = onNewClientDisconnect;
	}
	
}
