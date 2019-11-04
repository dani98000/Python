package il.co.ilrd.UDPTest;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;

public class Server {
	public static void main(String[] args) throws IOException {
		DatagramSocket socket = new DatagramSocket(8080);
		byte[] buf = new byte[512];
		DatagramPacket packet = new DatagramPacket(buf, buf.length);
		socket.receive(packet);
		int num = Integer.parseInt(new String(packet.getData()).trim());
		System.out.println("[Server]: Received " + num);
		byte[] buf2 = ("" + num*num).getBytes(); 
		System.out.println("[Server]: Sending " + num * num);
		socket.send(new DatagramPacket(buf2, buf2.length, packet.getAddress(), packet.getPort()));
	}
}
