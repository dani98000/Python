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
	private final static Executor threadPool = Executors.newCachedThreadPool();
	
	public HttpRequestHandler(HttpServer server) {
		this.server = server;
		server.setExecutor(threadPool);
		server.createContext("/", new HttpHandlerImpel());
	}
	
	private static class HttpHandlerImpel implements HttpHandler {
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
			Command command = CommandFactory.getCommand(commandName);
			threadPool.execute(() -> {
				CompletableFuture<HttpResponse<byte[]>> response;
				try {
					response = command.execute(body);
					response.thenAcceptAsync((httpResponse)-> {
						try {
							exchange.sendResponseHeaders(httpResponse.statusCode(), 0);
							exchange.getResponseBody().write(httpResponse.body());
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
