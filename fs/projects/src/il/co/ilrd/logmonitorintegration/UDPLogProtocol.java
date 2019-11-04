package il.co.ilrd.logmonitorintegration;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.SocketAddress;
import java.net.SocketException;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.TimeoutException;

public class UDPLogProtocol implements Protocol<String>{
	private DatagramSocket socket = new DatagramSocket();
	private SocketAddress remoteAddress;
	private int messageLength = 1024;
	private final int numTries = 10;
	private final int timeToWait = 10;
	private final TimeUnit unit = TimeUnit.MILLISECONDS;
	
	public UDPLogProtocol(SocketAddress bindAddress, SocketAddress remoteAddress)
			throws SocketException {
		socket = new DatagramSocket(bindAddress);
		this.remoteAddress = remoteAddress;
	}
	
	public UDPLogProtocol(SocketAddress bindAddress) throws SocketException {
		this(bindAddress, null);
	}

	
	@Override
	public void send(String data) throws IOException {
		int triesLeft = numTries;
		byte[] buf = new byte[messageLength];
		System.arraycopy(data.getBytes(), 0, buf, 0, data.length());
		DatagramPacket packet = new DatagramPacket(buf, messageLength, remoteAddress);
		
		while(--triesLeft != 0) {
			socket.send(new DatagramPacket(buf, messageLength, remoteAddress));
			System.out.println("message sent: " + new String(packet.getData()));
			try {
				receive(packet, unit, timeToWait);
				System.out.println("received ACK");
				
				return; //received ACK
			}catch(TimeoutException e) {}
		}
		
		throw new IOException("Didnt receive ACK from: " + remoteAddress);
		
	}

	@Override
	public String receive() throws IOException {
		byte[] buf = new byte[messageLength];
		DatagramPacket packet = new DatagramPacket(buf, messageLength);
		socket.receive(packet);
		String data = new String(buf).trim();
		socket.send(packet);
		
		return data;
	}
	
	public void receive(DatagramPacket packet, TimeUnit unit, long timeout)
			throws TimeoutException, IOException {
			long longMillis = TimeUnit.MILLISECONDS.convert(timeout, unit);
			
			int intMillis = (int) Math.min(Integer.MAX_VALUE, longMillis);

			socket.setSoTimeout(intMillis);
			while(true) {
			    try {
			    	socket.receive(packet);
			    }finally {
					socket.setSoTimeout(0);
			    }			
			}
		}
}
