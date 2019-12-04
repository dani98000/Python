package il.co.ilrd.networking;

import java.io.IOException;
import java.net.ProtocolException;
import java.net.SocketException;
import java.util.ArrayList;
import java.util.List;

public class ServerLogProtocol implements ServerProtocol{
	private final ServerAdapter adapter;
	private final List<byte[]> messages = new ArrayList<>();
	
	public ServerLogProtocol(String ip, int port) throws SocketException {
		adapter = new UDPServerAdapter(ip, port);
	}

	@Override
	public byte[] receiveData() throws ProtocolException {
		byte[] data = null;
		try {
			Message message = adapter.receive();
			data = message.getData();
			message.reply(data);
		} catch (IOException e) {
			e.printStackTrace();
		}
		
		if(!messages.contains(data)) {
			messages.add(data);
			
			return Validator.unWrap(data);						
		}else {
			return null;
		}
	}
}
