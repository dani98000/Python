package il.co.ilrd.crudserver;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.SocketException;
import java.net.SocketTimeoutException;
import java.util.concurrent.TimeUnit;

public class UDPClientProtocol implements ClientProtocol{
	private ClientAdapter adapter;
	private final int numTries = 10;
	private final int timeToWait = 10;
	private final TimeUnit unit = TimeUnit.MILLISECONDS;
	
	public UDPClientProtocol(String ip, int port) throws SocketException {
		adapter = new UDPClientAdapter(ip, port);
	}
	
	@Override
	public void SendData(byte[] data) throws IOException {
		int triesLeft = numTries;
		
		while(--triesLeft != 0) {
			adapter.send(Validator.wrap(data));
			System.out.println("sending...");
			try{
				adapter.receive(timeToWait, unit);
			}catch(SocketTimeoutException e) {}
			System.out.println("received ACK");
			
			return; //received ACK
		}
	}
}
