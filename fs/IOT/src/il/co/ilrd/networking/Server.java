package il.co.ilrd.networking;

import java.net.ProtocolException;
import java.util.ArrayList;
import java.util.List;
import java.util.function.Consumer;

public class Server {
	private final ServerProtocol protocol;
	private List<Consumer<byte[]>> onNewMessage;
	
	public Server(ServerProtocol protocol) {
		this.protocol = protocol;
		onNewMessage = new ArrayList<>();
	}

	public void start() {
		while(true) {
			byte[] data = null;
			
			try {
				data = protocol.receiveData();
			} catch (ProtocolException e) {
				System.err.println("Corrupted Message");
			}
			
			System.out.println("[Server] got update: " + new String(data).trim());
			for(Consumer<byte[]> consumer : onNewMessage) {
				consumer.accept(data);				
			}
		}
	}
	
	public void registerNewMessage(Consumer<byte[]> onNewMessage) {
		this.onNewMessage.add(onNewMessage);
	}
}
