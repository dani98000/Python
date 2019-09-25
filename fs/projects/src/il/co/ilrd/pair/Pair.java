package il.co.ilrd.pair;

import java.util.Comparator;
import java.util.Map;
import java.util.Map.Entry;

public class Pair<K, V> implements Map.Entry{
	K key;
	V value;
	
	private Pair(){}
	
	public static <K, V> Pair<K, V> of(K key, V value) {
		Pair<K, V> pair = new Pair<>();
		pair.setKey(key);
		pair.setValue(value);
		
		return pair;
	}
	
	@Override
	public Object getKey() {
		return key;
	}

	@Override
	public Object getValue() {
		return value;
	}

	@SuppressWarnings("unchecked")
	@Override
	public Object setValue(Object value) {
		V temp = this.value;
		this.value = (V)value;
		
		return temp;
	}
	
	public void setKey(K key) {
		this.key = key;
	}
	
	@Override
	public String toString() {
		return ("key : " + key +" with value : " + value);
	}
	
	@SuppressWarnings("unchecked")
	@Override
	public boolean equals(Object obj) {
		if(obj instanceof Pair) {
			return ((Pair<K, V>)obj).getKey() == this.getKey() && 
				   ((Pair<K, V>)obj).getValue() == this.getValue();
		}
		
		return false;
	}
	
	@Override
	public int hashCode() {
		return (int)this.getKey() * (int)this.getValue();
	}
	
	static <T extends Comparable<T>> Pair<T,T> minMax(T[] arr) {
		T min = arr[0];
		T max = arr[0];
		
		for(T t : arr) {
			if(t.compareTo(max) < 0) {
				max = t;
			}
		}
		
		return null;
	}
	
	static <T> Pair<T,T> minMax(T[] arr, Comparator<T> comp){
		return null;
	}
}
