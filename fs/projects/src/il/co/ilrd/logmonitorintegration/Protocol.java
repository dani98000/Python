package il.co.ilrd.logmonitorintegration;

import java.io.IOException;

public interface Protocol<T> {
	void send(T data) throws IOException;
	T receive() throws IOException;
}
