package il.co.ilrd.factory;
import java.util.HashMap;
import java.util.Map;
import java.util.function.Function; 

public class Factory<K, D, T> {
	private Map<K, Function<D,? extends T>> mapOfFunctions = new HashMap<>();
	
	public T create(K key) {
		return mapOfFunctions.get(key).apply(null);
	}
	
	public void add(K key, Function<D, ? extends T> function) {		
		mapOfFunctions.put(key, function);
	}
	
	public T create(K key, D args) {
		return mapOfFunctions.get(key).apply(args);
	}
}
