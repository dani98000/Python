package il.co.ilrd.networking;

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
	private final SocketAddress remoteAddress;
	private final DatagramSocket socket;
	
	public UDPClientAdapter(String ip, int port) throws SocketException {
		remoteAddress = new InetSocketAddress(ip, port);
		socket = new DatagramSocket();
	}
	
	@Override
	public void send(byte[] msg) throws IOException{
		socket.send(new DatagramPacket(msg, msg.length, remoteAddress));
	}

	@Override
	public byte[] receive(long timeout, TimeUnit timeUnit) throws IOException {
		long longMillis = TimeUnit.MILLISECONDS.convert(timeout, timeUnit);
		int intMillis = (int) Math.min(Integer.MAX_VALUE, longMillis);
		byte[] buf = new byte[1024];
		DatagramPacket packet = new DatagramPacket(buf, buf.length);

		socket.setSoTimeout(intMillis);
		socket.receive(packet);
		
		return packet.getData();
	}
}
