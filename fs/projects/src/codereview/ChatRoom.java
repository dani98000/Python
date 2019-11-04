package codereview;

import java.io.IOException;

public class ChatRoom {
	private ChatSrever server;
	private UserManager userManager;
	
	public ChatRoom(ChatSrever server) {
		this.server = server;
		userManager = new UserManager();
		server.registerNewClientMethod(t -> {
			try {
				userManager.onNewClient(t);
			} catch (IOException e) {
				e.printStackTrace();
			}
		});
		server.registerMessageMethod((t, u) -> {
			try {
				userManager.onNewMessage(t, u);
			} catch (IOException e) {
				e.printStackTrace();
			}
		});
		server.RegisterClientDisconnectMethod(t -> {
			try {
				userManager.onNewClientDisconnect(t);
			} catch (IOException e) {
				e.printStackTrace();
			}
		});
	}
	
	public void StartChat() throws IOException {		
		server.openChatServer();
	}
	
	public static void main(String[] args) {
		ChatRoom myChat = new ChatRoom(new TCPSrever());
		
		try {
			myChat.StartChat();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
}
