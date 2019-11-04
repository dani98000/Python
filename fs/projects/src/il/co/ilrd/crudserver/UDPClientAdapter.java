package il.co.ilrd.crudserver;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetSocketAddress;
import java.net.SocketAddress;
import java.net.SocketException;
import java.net.SocketTimeoutException;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.TimeoutException;

public class UDPClientAdapter implements ClientAdapter{
	private SocketAddress remoteAddress;
	private DatagramSocket socket;
	private DatagramPacket packet;
	private final int numTries = 10;
	private final int timeToWait = 10;
	private final TimeUnit unit = TimeUnit.MILLISECONDS;
	
	public UDPClientAdapter(String ip, int port) throws SocketException {
		remoteAddress = new InetSocketAddress(ip, port);
		socket = new DatagramSocket();
	}
	
	@Override
	public void send(byte[] msg) throws IOException{
		packet = new DatagramPacket(msg, msg.length);
		socket.send(new DatagramPacket(msg, msg.length, remoteAddress));
		System.out.println("message sent: " + new String(packet.getData()));
	}

	@Override
	public byte[] receive(long timeout, TimeUnit timeUnit) throws IOException {
		long longMillis = TimeUnit.MILLISECONDS.convert(timeout, timeUnit);
		int intMillis = (int) Math.min(Integer.MAX_VALUE, longMillis);

		socket.setSoTimeout(intMillis);
		socket.receive(packet);
		
		return packet.getData();
	}
}
