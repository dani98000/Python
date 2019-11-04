package il.co.ilrd.crudserver;

import java.io.IOException;

public interface ServerAdapter{
	public Message receive() throws IOException;
}
