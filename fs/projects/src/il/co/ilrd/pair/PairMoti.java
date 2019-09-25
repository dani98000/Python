package il.co.ilrd.pair;

import java.util.Comparator;
import java.util.Map;

public class PairMoti <K, V> implements Map.Entry<K,V>  {
	private K key;
	private V value;
	
	private PairMoti(K key, V value) {
		this.key = key;
		this.value = value;
	}
	
	public static <Q, W> PairMoti<Q, W> of(Q key, W value) {
		return new PairMoti<Q, W>(key, value);		
	}
	
	@Override
	public K getKey() {
		return this.key;
	}
	
	@Override
	public V getValue() {
		return this.value;
	}
	
	public void setKey(K key) {
		this.key = key;
	}
	
	@Override
	public V setValue(Object value) {
		return null;
	}
	
	@Override
	public String toString() {
		return "key: " + getKey() + " value: " + getValue();
	}
	
	@Override
	public boolean equals(Object obj) {
		if (obj instanceof PairMoti) {
			@SuppressWarnings("unchecked")
			PairMoti<K, V> pairObj = (PairMoti<K, V>) obj;
			return null == getKey() ? null == pairObj.getKey() : getKey().equals(pairObj.getKey())  &&
					(null == getValue() ? null == pairObj.getValue() : getValue().equals(pairObj.getValue()));			
		}
		
		return false;
	}
	
	@Override
	public int hashCode() {
		return (null == getKey() ? 0 : getKey().hashCode()) ^
			     (null == getValue() ? 0 : getValue().hashCode());
	}
	
	public static <T extends Comparable<T>> PairMoti<T,T> minMax(T[] array) {
		return minMax(array, (T o1, T o2) -> o1.compareTo(o2));
	} 
	
	public static <T> PairMoti<T,T> minMax(T[] array, Comparator<T> comparator) {
		T maximum = array[array.length -1];
		T minimum = array[array.length -1];
		
		for (int i = 0; i < array.length - 1; i += 2) {
			if (comparator.compare(array[i], array[i + 1]) > 0) {
				if (comparator.compare(array[i], maximum) > 0) {
					maximum = array[i];
				}
				if (comparator.compare(array[i + 1], minimum) < 0) {
					minimum = array[i + 1];
				}
				
			}else {
				if (comparator.compare(array[i + 1], maximum) > 0) {
					maximum = array[i + 1];
				}
				if (comparator.compare(array[i], minimum) < 0) {
					minimum = array[i];
				}
			}
		}
		return PairMoti.of(minimum, maximum);
	}	
}
