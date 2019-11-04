package il.co.ilrd.crudserver;

import java.io.IOException;
import java.net.SocketException;
import java.util.concurrent.TimeUnit;

public interface ClientAdapter {
	public void send(byte[] msg) throws IOException;
	public byte[] receive(long timeout, TimeUnit timeUnit) throws IOException;
}
