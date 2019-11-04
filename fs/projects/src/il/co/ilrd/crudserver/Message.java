package il.co.ilrd.crudserver;

public interface Message {
	public void reply(byte[] buffer);
	public byte[] getData();
}
