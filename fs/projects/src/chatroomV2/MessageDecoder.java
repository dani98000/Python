package chatroomV2;

import java.io.IOException;
import java.nio.ByteBuffer;

public class MessageDecoder {
	public static String decodeMessage(ByteBuffer buf) throws IOException {
		String encodedMessage = new String(buf.array(), 0, buf.limit());
		
		if (buf.limit() < 4 
				|| !encodedMessage.startsWith("#@") && !encodedMessage.endsWith("#@")){
				throw new IOException("message was not encoded "
						+ "according to protocol " + buf);
		}
		
		return encodedMessage.substring(2, buf.limit() - 2);
	}
	
	public static ByteBuffer encodeMessage(String message) {
		return ByteBuffer.wrap(("#@" + message + "#@").getBytes());
	}
}
