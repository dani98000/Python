package il.co.ilrd.pair;

import java.util.Comparator;
import java.util.Map;

public class Pair<K,V> implements Map.Entry<K,V>{
	K key;
	V value;
	
	private Pair(K key, V value){
		this.key = key;
		this.value = value;
	}
	
	public static <K,V> Pair<K,V> of(K key, V value) {
		return new Pair<K,V>(key, value);
	}
	
	@Override
	public K getKey() {
		return key;
	}

	@Override
	public V getValue() {
		return value;
	}

	@Override
	public V setValue(V value) {
		V temp = this.value;
		this.value = value;
		
		return temp;
	}
	
	public K setKey(K key) {
		K temp = this.key;
		this.key = key;
		
		return temp;
	}
	
	@Override
	public String toString() {
		return ("key : " + key +" with value : " + value);
	}
	
	@Override
	public boolean equals(Object obj) throws ClassCastException {
		if(!(obj instanceof Pair)) {
			throw new ClassCastException();
		}
		
		@SuppressWarnings("unchecked")
		Pair<K,V> pair = (Pair<K,V>)obj;

		return (getKey() == null ? 
				pair.getKey() == null : pair.getKey().equals(getKey()) &&
			   (getValue() == null ? 
			    pair.getValue() == null : pair.getValue() == getValue()));
	}
	
	@Override
	public int hashCode() {
		if(getKey() == null || getValue() == null) {
			return 0;
		}
		
		return getKey().hashCode() ^ getValue().hashCode();
	}
	
	static <T extends Comparable<T>> Pair<T,T> minMax(T[] arr) {
		return minMax(arr, ((T o1, T o2) -> o1.compareTo(o2)));
	}
	
	static <T> Pair<T,T> minMax(T[] arr, Comparator<T> comp) {
		T min = arr[0];
		T max = arr[0];
		int limit = (arr.length % 2 == 0) ? 1 : 0;
		
		for(int i = arr.length-1 ; i > limit; i-= 2) {
			if(comp.compare(arr[i], arr[i-1]) > 0){
				if(comp.compare(max, arr[i]) < 0) {
					max = arr[i];
				} else if(comp.compare(min, arr[i-1]) > 0) {
					min = arr[i];
				}
			}else {
				if(comp.compare(min, arr[i]) > 0) {
					min = arr[i];
				} else if(comp.compare(max, arr[i-1]) < 0) {
					max = arr[i-1];
				}
			}			
		}

		return Pair.of(min, max);
	}
}
