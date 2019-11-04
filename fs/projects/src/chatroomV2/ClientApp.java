package chatroomV2;

import java.awt.EventQueue;
import java.io.IOException;
import java.util.function.BiConsumer;
import java.util.function.Consumer;

public class ClientApp {
	private TCPClient tcpClient;
	private static ClientGUI clientGUI;
	
	public ClientApp() throws IOException {
		tcpClient = new TCPClient();
		clientGUI = new ClientGUI();
		clientGUI.registerOnConnect(onConnect);
		clientGUI.registerOnMessage(onMessage);
	}
	
	BiConsumer<String, Integer> onConnect = (ip, port)->{
		try {
			tcpClient.connect(ip, port);
			tcpClient.start();
		} catch (IOException e) {
			e.printStackTrace();
		}
	};
	
	Consumer<String> onMessage = (message)-> {
		tcpClient.sendMessage(message);
	};
	
	public static void main(String[] args) throws IOException {
		ClientApp client = new ClientApp();
		EventQueue.invokeLater(new Runnable(){
            @Override
            public void run(){
            	clientGUI.setVisible(true);
            }
        });
	}
}
