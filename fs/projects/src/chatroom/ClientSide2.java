package chatroom;

import java.io.IOException;
import java.net.InetSocketAddress;
import java.nio.ByteBuffer;
import java.nio.channels.SocketChannel;
import java.util.Scanner;

public class ClientSide2 {
	SocketChannel client = null;
	ByteBuffer buffer = null;
	Scanner scanner = new Scanner(System.in);
	String msg = null;
	
	
	class SendMessageThread extends Thread{
		ByteBuffer messageToSend = null;
		
		@Override
		public void run() {
			while(true) {
				msg = scanner.nextLine();
				messageToSend = ByteBuffer.wrap(msg.getBytes());
				try {
					client.write(messageToSend);
				} catch (IOException e) {
					e.printStackTrace();
				}
			}
		}
	}
	
	public void start() {
		SendMessageThread t1= new SendMessageThread();
		t1.start();
		
		try {
			client = SocketChannel.open(new InetSocketAddress("localhost", 1234));
			buffer = ByteBuffer.allocate(256);
		} catch (IOException e) {
		    e.printStackTrace();
		}
		
		while(true) {
	        String response = null;
	        try {
	        	buffer.clear();
	            if(client.read(buffer) == -1) {
	            	System.out.println("Server is closed sorry");
	            	return;
	            }
	            response = new String(buffer.array(),0,buffer.position());
	            buffer.flip();
	            System.out.println("response =" + response);
	        } catch (IOException e) {
	            e.printStackTrace();
	        }
		}
	}
	
	public static void main(String[] args) {		
		ClientSide2 c = new ClientSide2();
		c.start();
	}
}
