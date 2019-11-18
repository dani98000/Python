package il.co.ilrd.pingpong;

import java.io.IOException;
import java.net.InetSocketAddress;
import java.nio.ByteBuffer;
import java.nio.channels.SocketChannel;
import java.util.Scanner;

public class TCPSelectorClient {
	public static void main(String[] args) throws InterruptedException {
	   SocketChannel client = null;
	   ByteBuffer buffer;
	   
        try {
            client = SocketChannel.open(new InetSocketAddress("localhost", 5454));
            buffer = ByteBuffer.allocate(256);
        } catch (IOException e) {
            e.printStackTrace();
        }
        
        while(true) {
	        String msg = "Ping";
	        buffer = ByteBuffer.wrap(msg.getBytes());
	        String response = null;
	        try {
	            client.write(buffer);
	            Thread.sleep(1000);
	            buffer.clear();
	            client.read(buffer);
	            response = new String(buffer.array()).trim();
	            System.out.println("response =" + response);
	            buffer.clear();
	        } catch (IOException e) {
	            e.printStackTrace();
	        }
        }
	}
}
