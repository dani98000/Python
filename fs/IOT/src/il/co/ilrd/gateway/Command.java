package il.co.ilrd.gateway;

import java.io.IOException;
import java.net.http.HttpResponse;
import java.util.concurrent.CompletableFuture;

public interface Command {
	public CompletableFuture<HttpResponse<byte[]>> execute(byte[] body) throws IOException;
}
