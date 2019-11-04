package il.co.ilrd.crudserver;

import java.io.IOException;

public class Validator {
	public static byte[] wrap(byte[] buf) {
		return (("$@" + new String(buf).trim() + "$@").getBytes());
	}
	
	public static byte[] unWrap(byte[] buf) throws IOException {
		String encodedMessage = new String(buf).trim();
		
		if (buf.length < 4 
				|| !encodedMessage.startsWith("$@") && !encodedMessage.endsWith("$@")){
				throw new IOException("message was not encoded "
						+ "according to protocol " + buf);
		}
		
		return encodedMessage.substring(2, encodedMessage.length()-2).getBytes();
	}
}
