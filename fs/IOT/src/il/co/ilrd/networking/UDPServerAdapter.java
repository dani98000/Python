package il.co.ilrd.networking;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetSocketAddress;
import java.net.SocketException;
import java.util.Arrays;
import java.util.concurrent.TimeUnit;

public class UDPServerAdapter implements ServerAdapter{
	private final DatagramSocket socket;
	private static final int MSG_LENGTH = 1024;
	
	public UDPServerAdapter(String ip, int port) throws SocketException {
		socket = new DatagramSocket(new InetSocketAddress(ip, port));
	}
	
	@Override
	public Message receive() throws IOException {
		byte[] buf = new byte[MSG_LENGTH];
		DatagramPacket packet = new DatagramPacket(buf, MSG_LENGTH);
		socket.receive(packet);
		Message message = new MessageImpl(packet);
		
		return message;
	}
	
	private class MessageImpl implements Message {
		DatagramPacket packet;
		
		public MessageImpl(DatagramPacket packet) {
			this.packet = packet;
		}
		
		public byte[] getData() {
			return Arrays.copyOf(packet.getData(), packet.getLength());
		}
		
		@Override
		public void reply(byte[] buffer) {
			try {
				socket.send(new DatagramPacket(buffer, buffer.length, packet.getAddress(), packet.getPort()));
			} catch (IOException e) {
				e.printStackTrace();
			}
		}
	}
}