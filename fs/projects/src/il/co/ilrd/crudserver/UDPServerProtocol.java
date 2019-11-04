package il.co.ilrd.crudserver;

import java.io.IOException;
import java.net.SocketException;

public class UDPServerProtocol implements ServerProtocol{
	private ServerAdapter adapter;
	
	public UDPServerProtocol(String ip, int port) throws SocketException {
		adapter = new UDPServerAdapter(ip, port);
	}

	@Override
	public byte[] receiveData() {
		byte[] data = null;
		try {
			Message message = adapter.receive();
			data = Validator.unWrap((message.getData()));
			message.reply(data);
		} catch (IOException e) {
			e.printStackTrace();
		}
		
		return data;
	}
}
