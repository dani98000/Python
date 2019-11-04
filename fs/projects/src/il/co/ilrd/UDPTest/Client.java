package il.co.ilrd.UDPTest;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.InetSocketAddress;
import java.net.SocketException;

public class Client {
	public static void main(String[] args) throws IOException {
		DatagramSocket socket = new DatagramSocket();
		String num = "5";
		byte[] buf = num.getBytes();
		DatagramPacket packet = new DatagramPacket(buf, buf.length, InetAddress.getLocalHost(), 8080);
		socket.send(packet);
		System.out.println("[Client]: Sending " + num);
		
		byte[] buf2 = new byte[512];
		DatagramPacket packet2 = new DatagramPacket(buf2, buf2.length);
		socket.receive(packet2);
		System.out.print("[Client] received ");
		System.out.println(new String(packet2.getData()));
		
	}
}
