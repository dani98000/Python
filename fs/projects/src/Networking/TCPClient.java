package Networking;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.InetAddress;
import java.net.Socket;

public class TCPClient {
    private Socket socket;
    
    private TCPClient(int serverPort) throws Exception {
        this.socket = new Socket(InetAddress.getLocalHost(), serverPort);
    }
    
    private void start() throws IOException, InterruptedException {
        String input = "Pong";
        String dataReceived = null;
        String serverAddress = socket.getInetAddress().getHostAddress();

        while (true) {
        	//Send Message to server
            PrintWriter out = new PrintWriter(this.socket.getOutputStream(), true);
            out.println(input);
            out.flush();
            
		    Thread.sleep(1000);
		    
		    //Receive message from server
            BufferedReader in = new BufferedReader(
            new InputStreamReader(socket.getInputStream()));        
            dataReceived = in.readLine();
            System.out.println("\r\nMessage from " + serverAddress + ": " + dataReceived);
        }
    }
    
    public static void main(String[] args) throws Exception {
    	TCPClient client = new TCPClient(1234);
        
        System.out.println("\r\nConnected to Server: " + client.socket.getInetAddress());
        client.start();                
    }
}
