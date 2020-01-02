package il.co.ilrd.gateway;

import java.io.IOException;
import java.net.http.HttpResponse;
import java.util.concurrent.CompletableFuture;
import java.util.concurrent.Executor;
import java.util.concurrent.Executors;
import com.google.gson.JsonObject;
import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

public class HttpRequestHandler {
	private HttpServer server;
	private final CommandFactory commandFactory = CommandFactory.getInstance();
	private final static Executor threadPool = Executors.newCachedThreadPool();
	
	public HttpRequestHandler(HttpServer server) {
		this.server = server;
		server.setExecutor(threadPool);
		server.createContext("/", new HttpHandlerImpel());
	}
	
	public void start() {
		server.start();
		System.out.println("server is running...");
	}
	
	private class HttpHandlerImpel implements HttpHandler {
		@Override
		public void handle(HttpExchange exchange) throws IOException {
			String requestMethod = exchange.getRequestMethod();
			
			switch(requestMethod) {
				case "POST" : 
				doPost(exchange);
					break;
				case "GET" :
					doGet(exchange);
					break;
			}			
		}
		
		private void doPost(HttpExchange exchange) throws IOException {
			byte[] body = exchange.getRequestBody().readAllBytes();
			JsonObject json = JsonUtil.toJsonObject(new String(body));
			String commandName = json.get("commandType").getAsString();
			if(!commandFactory.isSupported(commandName)) {
				throw new IllegalArgumentException("Command not Supported");
			}
			Command command = commandFactory.getCommand(commandName);
			threadPool.execute(() -> {
				CompletableFuture<HttpResponse<String>> response;
				try {
					response = command.execute(json.get("data").getAsString());
					response.thenAcceptAsync((httpResponse)-> {
						try {
							exchange.sendResponseHeaders(httpResponse.statusCode(), 0);
							exchange.getResponseBody().write(httpResponse.body().getBytes());
						} catch (IOException e) {
							e.printStackTrace();
						}
						
						exchange.close();
					});
				} catch (IOException e1) {
					e1.printStackTrace();
					exchange.close();
				}
			});			
		}
		
		private void doGet(HttpExchange exchange) throws IOException {
			//todo: Add query parsing and handle GET request.
		}
	}
}
