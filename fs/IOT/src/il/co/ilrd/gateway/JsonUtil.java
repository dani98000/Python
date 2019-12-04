package il.co.ilrd.gateway;

import com.google.gson.JsonObject;
import com.google.gson.JsonParser;

public class JsonUtil {
	public static JsonObject toJsonObject(String json) {
		return JsonParser.parseString(json).getAsJsonObject();
	}
}
