package il.co.ilrd.gateway;

import java.io.IOException;
import java.net.URI;
import java.net.http.HttpClient;
import java.net.http.HttpRequest;
import java.net.http.HttpRequest.BodyPublishers;
import java.net.http.HttpResponse;
import java.net.http.HttpResponse.BodyHandlers;
import java.util.HashMap;
import java.util.concurrent.CompletableFuture;

public class CommandFactory {
	private static HashMap<String, Command> actions = new HashMap<>();
	private static final Command CR = new CR();
	private static final Command ER = new ER();
	private static final Command Updates = new Updates();
	
	private CommandFactory() {}
	
	private static class CR implements Command {
		public CR() {
			actions.put("CR", this);
		}

		@Override
		public CompletableFuture<HttpResponse<byte[]>> execute(byte[] data) throws IOException {
			HttpClient client = HttpClient.newHttpClient();
			
			HttpRequest req = HttpRequest.newBuilder()
					.uri(URI.create("http://localhost:8080/IOT/CR"))
					.header("Content-Type", "application/json")
					.POST(BodyPublishers.ofByteArray(data))
					.build();
			
			return client.sendAsync(req, BodyHandlers.ofByteArray());
		}
	} 
	
	private static class ER implements Command {
		public ER() {
			actions.put("ER", this);
		}

		@Override
		public CompletableFuture<HttpResponse<byte[]>> execute(byte[] data) throws IOException {
			HttpClient client = HttpClient.newHttpClient();
			
			HttpRequest req = HttpRequest.newBuilder()
					.uri(URI.create("http://localhost:8080/IOT/ER"))
					.header("Content-Type", "application/json")
					.POST(BodyPublishers.ofByteArray(data))
					.build();
			
			return client.sendAsync(req, BodyHandlers.ofByteArray());
		}
	} 

	private static class Updates implements Command {
		public Updates() {
			actions.put("Updates", this);
		}

		@Override
		public CompletableFuture<HttpResponse<byte[]>> execute(byte[] data) throws IOException {
			HttpClient client = HttpClient.newHttpClient();
			
			HttpRequest req = HttpRequest.newBuilder()
					.uri(URI.create("http://localhost:8080/IOT/Updates"))
					.header("Content-Type", "application/json")
					.POST(BodyPublishers.ofByteArray(data))
					.build();
			
			return client.sendAsync(req, BodyHandlers.ofByteArray());
		}
	} 

	public static Command getCommand(String commandName) {
		return actions.get(commandName);
	}
}
