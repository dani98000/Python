package chatroomV2;

import java.io.IOException;
import java.util.HashMap;
import java.util.function.BiConsumer;
import java.util.function.Consumer;

public class UserManager {
	private final HashMap<Client, User> users  = new HashMap<>();
	private final TCPServer tcpServer;
	
	public UserManager(String ip, int port) {
		tcpServer = new TCPServer(ip, port);
	}
	
	private BiConsumer<Client ,String> onNewMessage = (Client client ,String str)-> {
		if(!users.containsKey(client)) {
			for(Client curClient : users.keySet()) {
				curClient.sendMessage("[Server]" + str + " joined the chat");
			} 
			users.put(client, new User(str));
			System.out.println(str + " registered");
		}else {
			for(Client curClient : users.keySet()) {
				curClient.sendMessage("[" + users.get(client).getName() + "] " + str);
			}
		}
	};
    
	private Consumer<Client> onNewClient = (Client client)-> {
		client.sendMessage("Haalan Please write your name: ");
	};
	
	private Consumer<Client> onClientDisconnect = (Client client)-> {
		User user = users.get(client);
		if (null != user) {
			broadcastFromServer(user.getName() + " left the chat");
			users.remove(client);
		}
	};
	
	private void broadcastFromServer(String message) {
		for(Client curClient : users.keySet()) {
			curClient.sendMessage("[Server]" + message);
		}
	}
	
	public void start() {
		tcpServer.registerClientDisconnect(onClientDisconnect);
		tcpServer.registerNewMessage(onNewMessage);
		tcpServer.registerNewClient(onNewClient);
		try {
			tcpServer.start();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
	
	private class User{
		String name;
		
		public User(String name) {
			this.name = name;
		}
		
		public String getName() {
			return name;
		}
	}
	
	public static void main(String[] args) throws IOException, InterruptedException {
		UserManager server = new UserManager("localhost", 1234);
		server.start();
	}
}