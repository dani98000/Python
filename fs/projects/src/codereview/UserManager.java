package codereview;

import java.io.IOException;
import java.util.HashMap;
import java.util.Map.Entry;

public class UserManager {
	private HashMap<ComObject,Client> clients = new HashMap<>();  
	private Protocol protocol = new ChatProtocol();
	
	public void onNewClient(ComObject comObj) throws IOException {
		clients.put(comObj, null);
		
		comObj.handleMessage("What is your name?", "Wellcome");
	}
	
	public void onNewMessage(ComObject comObj, String message) throws IOException {
		if (null == clients.get(comObj)) {
			clients.put(comObj, new Client(protocol.unwrap(message)));
		} else {
			for(Entry<ComObject,Client> client : clients.entrySet()) {
				client.getKey().handleMessage(message, clients.get(comObj).getName());
			}
		}
	}
	
	public void onNewClientDisconnect(ComObject comObj) throws IOException {
		Client leftTheChat = clients.remove(comObj);
		
		for(ComObject Obj : clients.keySet()) {
			Obj.handleMessage("Left the chat.", leftTheChat.getName());					
		}
	}
	
	private static class Client {
		private String name;
		
		public Client(String name) {
			this.name = name;
		}
		
		public String getName() {
			return name;
		}
	}
}