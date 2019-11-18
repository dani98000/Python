package il.co.ilrd.networking;

import java.io.IOException;
import java.net.ProtocolException;

public class Validator {
	private static final String HEADER = "$@";
	private static final String FOOTER = "@$";
	
	public static byte[] wrap(byte[] buf) {
		String wrapped = HEADER + new String(buf) + FOOTER;
		
		return (wrapped.getBytes());
	}
	
	public static byte[] unWrap(byte[] buf) throws ProtocolException {
		String encodedMessage = new String(buf).trim();
		
		if (buf.length < 4 
			|| !encodedMessage.startsWith(HEADER) && !encodedMessage.endsWith(FOOTER)){
			throw new ProtocolException("message was not encoded "
			+ "according to protocol " + buf);
		}
						
		return encodedMessage.substring(HEADER.length(), 
										encodedMessage.length() - FOOTER.length()).getBytes();
	}
}
