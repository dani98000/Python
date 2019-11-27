package il.co.ilrd.networking;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.ProtocolException;
import java.net.SocketException;
import java.net.SocketTimeoutException;
import java.nio.ByteBuffer;
import java.util.Arrays;
import java.util.concurrent.TimeUnit;

import javax.sound.midi.Receiver;

public class ClientLogProtocol implements ClientProtocol{
	private final ClientAdapter adapter;
	private final int numTries = 10;
	private final int timeToWait = 1000;
	private final TimeUnit unit = TimeUnit.MILLISECONDS;
	
	public ClientLogProtocol(ClientAdapter adapter) throws SocketException {
		this.adapter = adapter;
	}
	
	public ClientLogProtocol(String ip, int port) throws SocketException {
		this.adapter = new UDPClientAdapter(ip, port);
	}
	
	@Override
	public void SendData(byte[] data) throws IOException {
		int currentSequenceNumber = 0;
		int triesLeft = numTries;
		ByteBuffer receivedData = null;
		
		ByteBuffer messageToSend = ByteBuffer.allocate(Integer.SIZE / 8 + data.length);
		messageToSend.putInt(currentSequenceNumber++);
		messageToSend.put(data);
		
		while(--triesLeft != 0) {
			adapter.send(Validator.wrap(messageToSend.array()));
			try{
				receivedData = ByteBuffer.wrap(Validator.unWrap(adapter.receive(timeToWait, unit)));
			}catch(SocketTimeoutException e) {}
			if(!(Arrays.equals(messageToSend.array(), receivedData.array()))) {
				throw new ProtocolException();
			}
			
			return; //received ACK
		}
	}
}
