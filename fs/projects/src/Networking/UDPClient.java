package Networking;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.util.Scanner;

public class UDPClient {
    private DatagramSocket udpSocket;
    private InetAddress serverAddress;
    private int port;
    private Scanner scanner;
    String messageToSend = "Ping";
    
    private UDPClient(int port) throws IOException {
        this.serverAddress = InetAddress.getLocalHost();
        this.port = port;
        udpSocket = new DatagramSocket();
        scanner = new Scanner(System.in);
    }
    
    private int start() throws IOException, InterruptedException {
        String in;
        while (true) {
            in = scanner.nextLine();
            if(in.equals("start")) {
            	while(true) {
                    DatagramPacket p = new DatagramPacket(
                    messageToSend.getBytes(), messageToSend.getBytes().length, serverAddress, port);    
                    this.udpSocket.send(p);    	
                    byte[] buf = new byte[256];
                    DatagramPacket packet = new DatagramPacket(buf, buf.length);
                        
                    // blocks until a packet is received
                    udpSocket.receive(packet);
                    Thread.sleep(1000);
                    String msg = new String(packet.getData()).trim();
                    System.out.println("Message from " + packet.getAddress().getHostAddress() + ": " + msg);
            	}
            }                
        }
    }

    public static void main(String[] args) throws NumberFormatException, IOException, InterruptedException {        
    	UDPClient sender = new UDPClient(7077);
    	System.out.println("-- Running UDP Client at " + InetAddress.getLocalHost() + " --");
    	sender.start();
    }
}