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
	private static final Command PR = new PR();
	private static final Command Updates = new Updates();
	
	private static final String URL = "http://localhost:8080";
	
	private CommandFactory() {}
	
	private static class CR implements Command {
		public CR() {
			actions.put("CR", this);
		}

		@Override
		public CompletableFuture<HttpResponse<byte[]>> execute(byte[] data) throws IOException {
			HttpClient client = HttpClient.newHttpClient();
			
			HttpRequest req = HttpRequest.newBuilder()
					.uri(URI.create(URL + "/iot/companies"))
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
					.uri(URI.create(URL + "/iot/endusers"))
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
					.uri(URI.create(URL + "/iot/updates"))
					.header("Content-Type", "application/json")
					.POST(BodyPublishers.ofByteArray(data))
					.build();
			
			return client.sendAsync(req, BodyHandlers.ofByteArray());
		}
	} 
	
	private static class PR implements Command {
		public PR() {
			actions.put("PR", this);
		}

		@Override
		public CompletableFuture<HttpResponse<byte[]>> execute(byte[] data) throws IOException {
			HttpClient client = HttpClient.newHttpClient();
			
			HttpRequest req = HttpRequest.newBuilder()
					.uri(URI.create(URL + "/iot/products"))
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
