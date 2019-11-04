package chatroomV2;

import java.io.IOException;
import java.net.InetSocketAddress;
import java.net.SocketAddress;
import java.nio.ByteBuffer;
import java.nio.channels.SocketChannel;

public class TCPClient implements AutoCloseable {
	private final SocketChannel client;
	private SocketAddress socketAddress;
	private MessageHandlerThread thread;
	private boolean shouldStop = false;
	private boolean isConnected = false;
	private boolean hasStarted = false;
	
	public TCPClient() throws IOException {
		client = SocketChannel.open();
	}
	
	public void connect(String ip, int port) throws IOException {
		if(!isConnected) {
			socketAddress = new InetSocketAddress(ip, port);
			try {
				client.connect(socketAddress);
				isConnected = true;
			} catch (IOException e) {
				throw new IOException("Coudln't connect to server");
			}
		}
	}
	
	public void sendMessage(String message) {
		try {
			client.write(MessageDecoder.encodeMessage(message));
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
	
	class MessageHandlerThread extends Thread {
		ByteBuffer buffer = ByteBuffer.allocate(256);

		@Override
		public void run() {
			while (!shouldStop) {
		        String response = null;
		        try {
		        	buffer.clear();
		            if(client.read(buffer) == -1) {
		            	System.out.println("Server is closed sorry");
						shouldStop = true;
		            	break;
		            }
		            response = MessageDecoder.decodeMessage(ByteBuffer.wrap(buffer.array(),
		            										0,buffer.position()));	            
		            buffer.flip();
		            System.out.println(response);
		        } catch (IOException e) {
		            e.printStackTrace();
		        }
			}
		}
	}
	
	public void start() {
		if(!isConnected) {
			throw new IllegalStateException("Not connected to the server");
		}
		if(hasStarted) {
			throw new IllegalStateException("Client is already up");
		}
		
		hasStarted = true;
		
		thread = new MessageHandlerThread();
		thread.start();
	}

	@Override
	public void close() throws Exception {
		shouldStop = true;
		client.close();
		thread.join();
	}
}
