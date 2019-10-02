package il.co.ilrd.hashmap;

import java.util.AbstractCollection;
import java.util.AbstractSet;
import java.util.ArrayList;
import java.util.Collection;
import java.util.ConcurrentModificationException;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.NoSuchElementException;
import java.util.Set;

public class HashMap<K,V> implements Map<K,V> {
	private List<List<Entry<K, V>>> map = new ArrayList<List<Entry<K,V>>>();
	private static final int DEFAULT_CAPACITY = 16;
	private int capacity;
	private Set<Entry<K, V>> entrySet = null;
	private Set<K> keySet = null;
	private Collection<V> values = null;
	ModCounter count = new ModCounter();
	
	public HashMap() {
		capacity = DEFAULT_CAPACITY;
		mapInit();
	}
	
	public HashMap(int capacity) {
		this.capacity = capacity;
		mapInit();
	}
	
	private void mapInit() {
		for(int i = 0; i < capacity; ++i) {
			map.add(i, new LinkedList<Entry<K,V>>());
		}
	}
	
	@Override
	public void clear() {
		count.increment();

		for(List<Entry<K,V>> list : map) {
			list.clear();
		}
	}

	@Override
	public boolean containsKey(Object key) {		
		for(K currKey : keySet()) {
			if(currKey.equals(key)) {
				return true;
			}
		}
		return false;
	}

	@Override
	public boolean containsValue(Object value) {
		for(V currValue : values) {
			if(currValue.equals(value)) {
				return true;
			}
		}
		return false;
	}

	@Override
	public Set<Entry<K, V>> entrySet() {
		return ((entrySet == null) ? entrySet = new EntrySet() : entrySet);
	}

	@Override
	public V get(Object key) {
		List<Entry<K,V>> list = getBucket(key);

		for(Entry<K, V> pair : list) {
			if(pair.getKey().equals(key)) {
				return pair.getValue();
			}
		}
		
		return null;
	}

	@Override
	public boolean isEmpty() {
		for(List<Entry<K,V>> list : map) {
			if (!list.isEmpty()) {
				return false;
			}
		}		
	
		return true;
	}

	@Override
	public Set<K> keySet() {
		return ((keySet == null) ? keySet = new KeySet() : keySet);
	}

	@Override
	public V put(K key, V value) {
		List<Entry<K,V>> bucket = getBucket(key);
		V retVal = null;
		
		if(this.containsKey(key)) {
			retVal = this.get(key);
			this.remove(key);
		}
		bucket.add(Pair.of(key, value));
		count.increment();
	
		return retVal;
	}


	@Override
	public void putAll(Map<? extends K, ? extends V> from) {
		for(Entry<? extends K, ? extends V> entry : from.entrySet()) {
			this.put(entry.getKey(), entry.getValue());
		}
	}

	@Override
	public V remove(Object key) {
		List<Entry<K, V>> bucket = getBucket(key);
		Iterator<Entry<K, V>> listIterator = bucket.iterator();
		
		count.increment();
		
		while(listIterator.hasNext()) {
			Entry<K, V>pair = listIterator.next();
			if(pair.getKey().equals(key)) {
				listIterator.remove();
				
				return pair.getValue();
			}
		}
		
		return null;
	}

	@Override
	public int size() {
		return values().size();
	}
	
	private List<Entry<K, V>> getBucket(Object key) {
		return map.get(Math.abs(key.hashCode() % capacity));
	}

	@Override
	public Collection<V> values() {
		return ((null == values) ? values = new Values() : values);	
	}
	
    private class EntrySet extends AbstractSet<Entry<K, V>> {
    	
        @Override
        public Iterator<Entry<K, V>>  iterator() {
            return new EntryIterator();
        }

        @Override
        public int size() {
        	int size = 0;
        	
            Iterator<Entry<K,V>> iter = new EntryIterator();
            while(iter.hasNext() && iter.next() != null) {
            	++size;
            }
            
            return size;
        }

	    private class EntryIterator implements Iterator<Entry<K, V>> {
	    	private int i = -1;
	    	private Iterator<List<Entry<K, V>>> bucketIterator = map.iterator();
	        private Iterator<Entry<K, V>> entryIterator = new ArrayList<Entry<K, V>>().iterator();
			private int currentModCount = count.getCount();
	        
	        private void getNextFilledBucked(){
	        	while (bucketIterator.hasNext() && !entryIterator.hasNext()) {
	        		entryIterator = bucketIterator.next().iterator();
				}
	        }
	        
	        @Override
	        public boolean hasNext() {
	        	count.verify(currentModCount);
	            if(!entryIterator.hasNext()) {
	            	getNextFilledBucked();
	            }
	            
				return entryIterator.hasNext() || bucketIterator.hasNext();
			}
	        
	        @Override
	        public Entry<K, V> next() {
	        	count.verify(currentModCount);

	        	if (!hasNext()) {
					throw new NoSuchElementException();
				}
	        	
	        	return entryIterator.next();
	        }
		}
    }
        	
    private class KeySet extends AbstractSet<K> {
    	@Override
    	public Iterator<K> iterator() {
    		return new KeyIterator();
    	}
    	
    	@Override
    	public int size() {
    		return entrySet().size();
    	}

    	private class KeyIterator implements Iterator<K> {
    		private Iterator<Map.Entry<K, V>> entries = entrySet().iterator();

    		@Override
    		public boolean hasNext() {
    			if(entries.hasNext()) {
    				return true;
    			}
    			return false;
    		}

    		@Override
    		public K next() {
    			K curr = entries.next().getKey();
    				
    			return curr;
    		}             
    	}	
    }

    private class Values extends AbstractCollection<V> {
    	@Override
    	public Iterator<V> iterator() {
    		return new ValueIterator();
    	}

    	@Override
    	public int size() {
    		return entrySet().size();
    	}

    	class ValueIterator implements Iterator<V> {
    		private Iterator<Map.Entry<K, V>> entries = entrySet().iterator();
    
    		@Override
    		public boolean hasNext() {
    			if(entries.hasNext()) {
    				return true;
    			}
    			return false;
    		}
    
    		@Override
    		public V next() {
    			Entry<K, V> curr = entries.next();
    	
    			if(null != curr) {
    				return curr.getValue();            		
    			}
    
    			return null;
    		}           
    	}
    }
    
	private static class ModCounter {
		private int counter = 0;
		
		public void increment() {
			++counter;
		}
		
		public int getCount() {
			return counter;
		}
		
		public void verify(int count) throws ConcurrentModificationException {
			if (this.counter != count) {
				throw new ConcurrentModificationException();
			}
		}
	}
}