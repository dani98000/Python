package il.co.ilrd.networking;

import java.io.IOException;
import java.net.URI;
import java.net.http.HttpClient;
import java.net.http.HttpClient.Builder;
import java.net.http.HttpRequest;
import java.net.http.HttpRequest.BodyPublishers;
import java.net.http.HttpResponse;
import java.util.concurrent.CompletableFuture;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.TimeoutException;

public class HTTPClientAdapter implements ClientAdapter{
	private final HttpClient client = HttpClient.newHttpClient();
	private CompletableFuture<HttpResponse<byte[]>> message;
	private byte[] responeBuf = null;
	
	@Override
	public void send(byte[] msg) throws IOException {
		  HttpRequest request = HttpRequest.newBuilder()
			        .uri(URI.create("http://localhost:8080/IOT"))
			        .header("Content-Type", "text/plain; charset=UTF-8")
			        .POST(BodyPublishers.ofByteArray(msg))
			        .build();
		  message = client.sendAsync(request, HttpResponse.BodyHandlers.ofByteArray());
	}

	@Override
	public byte[] receive(long timeout, TimeUnit timeUnit) throws IOException {
		HttpResponse<byte[]> res = null;
		
		try {
			res = message.get(timeout, timeUnit);
			responeBuf = res.body();
		} catch (InterruptedException | ExecutionException | TimeoutException e) {
			e.printStackTrace();
		}
		
		return res.body();
	}
}