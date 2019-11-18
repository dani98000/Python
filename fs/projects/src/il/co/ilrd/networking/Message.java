package il.co.ilrd.networking;

public interface Message {
	public void reply(byte[] buffer);
	public byte[] getData();
}
