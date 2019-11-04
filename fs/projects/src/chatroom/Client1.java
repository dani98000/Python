package chatroom;

import java.io.IOException;

import chatroomV2.TCPClient;

public class Client1 {
	public static void main(String[] args) throws IOException {		
		TCPClient client = new TCPClient();
		client.connect("localhost", 1234);
		client.start();
	}
}
