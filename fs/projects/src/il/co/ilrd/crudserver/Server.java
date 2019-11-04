package il.co.ilrd.crudserver;

import java.util.function.Consumer;

public class Server {
	protected ServerProtocol protocol;
	private Consumer<byte[]> onNewMessage;
	
	public Server(ServerProtocol protocol) {
		this.protocol = protocol;
	}

	public void start() throws InterruptedException {
		while(true) {
			byte[] data = protocol.receiveData();
			System.out.println("[Server] got update: " + new String(data).trim());
			onNewMessage.accept(data);
		}
	}
	
	public void registerNewMessage(Consumer<byte[]> onNewMessage) {
		this.onNewMessage = onNewMessage;
	}
}
