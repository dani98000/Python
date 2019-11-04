package codereview;
import java.io.IOException;
import java.nio.ByteBuffer;
import java.nio.channels.SocketChannel;

public class ComObjectTCP implements ComObject {
	private SocketChannel clientSocket;
	private Protocol protocol = new ChatProtocol();
	
	ComObjectTCP(SocketChannel clientSocket) {
		this.clientSocket = clientSocket;
	}
	
	@Override
	public void handleMessage(String message, String name) throws IOException {
		clientSocket.write(ByteBuffer.wrap(protocol.wrap(name + ": " + message).getBytes()));
	}
}
