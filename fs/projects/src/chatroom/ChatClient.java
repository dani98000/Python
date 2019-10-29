package chatroom;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.InetSocketAddress;
import java.net.SocketAddress;
import java.nio.ByteBuffer;
import java.nio.channels.SocketChannel;

public class ChatClient implements AutoCloseable {
	private static final String EXIT_MSG = "!exit!";
	
	private SocketChannel socketChannel;
	private volatile boolean shouldStop = false;
	
	public ChatClient(String serverHost, int serverPort) throws IOException {
		SocketAddress endPoint = new InetSocketAddress(serverHost, serverPort);
		
		socketChannel = SocketChannel.open();
		
		try {			
			socketChannel.connect(endPoint);
		} catch (IOException e) {
			throw new IOException("[-] could not connect to server: " + endPoint);
		}
	}
	
	public void run() throws IOException, InterruptedException {
		BufferedReader reader = new BufferedReader(
				new InputStreamReader(System.in));
		
		System.out.println("[+] enter \"!exit!\" to stop");

		MessagesFetchingThread thread = new MessagesFetchingThread();
		thread.start();
					
		while (!shouldStop) {

			while (!reader.ready() && !shouldStop) { // wait for input to be ready
				Thread.sleep(200);
			}
			
			if (shouldStop) {
				break;
			}
			
			String msg = reader.readLine();
			
			if (msg.contentEquals(EXIT_MSG)) {
				break;
			}
			
			ByteBuffer buf = ByteBuffer.wrap(msg.getBytes());
			
			try {
				socketChannel.write(buf);
			} catch (IOException e) {
				System.err.println("[-] error sending message: " + msg);
			}
		}
		
		shouldStop = true;
		socketChannel.close();
		reader.close();
		thread.join();
		
		System.out.println("bye!");
	}
	
	private class MessagesFetchingThread extends Thread {		
		@Override
		public void run() {			
			while (!shouldStop) {
				ByteBuffer buf = ByteBuffer.allocate(256);
				int bytesRead = 0;
				
				try {
					while (0 != (bytesRead = socketChannel.read(buf))) {						
						if (-1 == bytesRead) {
							System.out.println("[+] server was closed!");
							shouldStop = true;
							break;
						}
						
						System.out.println(new String(buf.array(),
								buf.position() - bytesRead, bytesRead));
					}
					
				} catch (IOException e) {
					if (!shouldStop) {						
						System.out.println("[-] Could not fetch messages from server.");
						shouldStop = true;
					}
				}
			}
		}
	}

	@Override
	public void close() throws Exception {
		if (null != socketChannel) {
			socketChannel.close();
		}
	}
	
	public static void main(String args[]) {
		if (args.length < 2) {
			System.err.println("[-] must provide hostname and port number. exiting...");
			System.exit(-1);
		}
		
		String host = args[0];
		int port = Integer.parseInt(args[1]);
		
		try (ChatClient client = new ChatClient(host, port)) {
			client.run();
		} catch (IOException e) {
			e.printStackTrace();
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
}
