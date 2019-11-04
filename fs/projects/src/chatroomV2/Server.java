package chatroomV2;

import java.util.function.BiConsumer;
import java.util.function.Consumer;

public interface Server<T> {
	public void registerNewClient(Consumer<T> onNewClient);
	public void registerClientDisconnect(Consumer<T> onClientDisconnect);
	public void registerNewMessage(BiConsumer<Client ,String> onNewMessage);
}
