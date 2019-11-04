package il.co.ilrd.crudserver;

import java.io.IOException;
import java.net.SocketException;

public interface ClientProtocol {
	public void SendData(byte[] data) throws IOException;
}
