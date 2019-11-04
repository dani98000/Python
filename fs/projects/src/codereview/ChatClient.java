package codereview;

import java.io.IOException;
import java.net.InetAddress;
import java.net.InetSocketAddress;
import java.net.UnknownHostException;
import java.nio.ByteBuffer;
import java.nio.channels.SocketChannel;
import java.util.Scanner;

public class ChatClient {
	private int portNumber;
	private InetAddress hostIP;
	private Protocol protocol;
	
	public ChatClient(int portNumber, InetAddress hostIP) throws UnknownHostException {
		this.portNumber = portNumber;
		this.hostIP = hostIP;
		protocol = new ChatProtocol();
	}
	
	public void start() throws IOException {
		InetSocketAddress socketAdress = new InetSocketAddress(hostIP, portNumber);
		SocketChannel clientChannel = SocketChannel.open(socketAdress);
		Listener listener = new Listener(clientChannel);
		Scanner scanner = new Scanner(System.in);
		
		listener.start();
		String sentence = protocol.wrap(scanner.nextLine()); 
		
		while(!sentence.equalsIgnoreCase("Goodbye")) {
			
			clientChannel.write(ByteBuffer.wrap(protocol.wrap(sentence).getBytes()));
			sentence = scanner.nextLine(); 
		}
		
		listener.shouldStop = true;	
		clientChannel.close();
		scanner.close();
	}

	public static void main(String[] args) throws IOException {
		ChatClient client = new ChatClient(7777, InetAddress.getLocalHost());
		client.start();
	}
	
	private class Listener extends Thread {
		private SocketChannel clientChannel;
		private volatile boolean shouldStop = false;
		
		public Listener(SocketChannel clientChannel) {
			this.clientChannel = clientChannel;
		}
		
		@Override
		public void run() {
			ByteBuffer inBuffer = ByteBuffer.allocate(1024);
			
			while(!shouldStop) {
				try {
					int read = clientChannel.read(inBuffer);
					if(-1 != read) {
						System.out.println(protocol.unwrap(new String(inBuffer.array(), 0, read)));						
					}
					inBuffer.clear();
				} catch (IOException e) {
					System.out.println("GoodBye");
				}
			}
		}
	}
}
