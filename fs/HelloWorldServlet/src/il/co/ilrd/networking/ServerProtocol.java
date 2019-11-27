package il.co.ilrd.networking;

import java.net.ProtocolException;

public interface ServerProtocol {
	public byte[] receiveData() throws ProtocolException;
}
