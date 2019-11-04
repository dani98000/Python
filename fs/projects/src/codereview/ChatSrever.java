package codereview;

import java.io.IOException;
import java.util.function.BiConsumer;
import java.util.function.Consumer;

public interface ChatSrever {
	void registerNewClientMethod(Consumer<ComObject> onNewClient);
	void registerMessageMethod(BiConsumer<ComObject, String> onNewMessage);
	void RegisterClientDisconnectMethod(Consumer<ComObject> onNewClientDisconnect);
	void openChatServer() throws IOException;
	void closeChatServer();
}
