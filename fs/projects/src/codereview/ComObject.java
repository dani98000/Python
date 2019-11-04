package codereview;

import java.io.IOException;

public interface ComObject {
	void handleMessage(String message, String name) throws IOException;
}
