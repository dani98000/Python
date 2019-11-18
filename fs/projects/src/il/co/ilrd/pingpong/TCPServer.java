package il.co.ilrd.pingpong;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.InetAddress;
import java.net.ServerSocket;
import java.net.Socket;

public class TCPServer {
	private ServerSocket server;
	
    public TCPServer() throws Exception {
          this.server = new ServerSocket(1234);
    }
    
    private void listen() throws Exception {
        String data = null;
        String message = "Ping";
        Socket client = this.server.accept();
        String clientAddress = client.getInetAddress().getHostAddress();
        System.out.println("\r\nNew connection from " + clientAddress);
        while(true)
        {        	
		    //Receive message from client
		    BufferedReader in = new BufferedReader(new InputStreamReader(client.getInputStream()));        
		    data = in.readLine();
		    System.out.println("\r\nMessage from " + clientAddress + ": " + data);
		    
		    Thread.sleep(1000);

		    //Send message to server
		    PrintWriter out = new PrintWriter(client.getOutputStream(), true);
            out.println(message);
            out.flush();
        }
    }
    
    public InetAddress getSocketAddress() {
        return this.server.getInetAddress();
    }
    
    public int getPort() {
        return this.server.getLocalPort();
    }
    public static void main(String[] args) throws Exception {
    	TCPServer app = new TCPServer();
        System.out.println("\r\nRunning Server: " + 
                "Host=" + app.getSocketAddress().getHostAddress() + 
                " Port=" + app.getPort());
        
        app.listen();
    }
}
