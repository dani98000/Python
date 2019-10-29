package Networking;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.SocketException;

public class UDPServer {
    private DatagramSocket udpSocket;
    private int port;
    String messageToSend = "Pong";
 
    public UDPServer(int port) throws SocketException, IOException {
        this.port = port;
        this.udpSocket = new DatagramSocket(this.port);
    }
    
    private void listen() throws Exception {
        System.out.println("-- Running Server at " + InetAddress.getLocalHost() + "--");
        String msg;
        
        while (true) {
            
            byte[] buf = new byte[256];
            DatagramPacket packet = new DatagramPacket(buf, buf.length);
            
            // blocks until a packet is received
            udpSocket.receive(packet);
            Thread.sleep(1000);
            msg = new String(packet.getData()).trim();
            
            System.out.println(
                    "Message from " + packet.getAddress().getHostAddress() + ": " + msg);
            
            DatagramPacket p = new DatagramPacket(
            		messageToSend.getBytes(), messageToSend.getBytes().length, packet.getAddress(), packet.getPort());
                
            this.udpSocket.send(p); 

        }
    }
    
    public static void main(String[] args) throws Exception {
    	UDPServer client = new UDPServer(7077);
    	client.listen();
    }
}