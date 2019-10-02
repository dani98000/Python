package il.co.ilrd.hashmap;

import java.util.ConcurrentModificationException;
import java.util.Iterator;
import java.util.Map.Entry;

import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.Assertions;


class HashMapTest {

	@Test
	void test1() {
		HashMap<Integer, String> map= new HashMap<>();
		
		Assertions.assertNotNull(map);
		Assertions.assertEquals(0, map.size());
		
		map.put(1, "Daniel");
		map.put(2, "Yael");
		map.put(3, "Eran");
		map.put(4, "Roi");
		map.put(5, "Inbar");
		map.put(6, "Alex");
		map.put(7, "Mishel");
		map.put(8, "Moti");
		map.put(9, "Eldad");
		
		Assertions.assertEquals(9, map.size());
		Assertions.assertTrue(map.containsKey(2));
		Assertions.assertTrue(map.containsValue("Daniel"));
		
		String temp = map.put(1, "Omer");
		
		Assertions.assertEquals("Daniel", temp);
		Assertions.assertEquals(9, map.size());

		temp = map.remove(5);
		Assertions.assertEquals("Inbar", temp);
		Assertions.assertEquals(8, map.size());

		map.clear();
		Assertions.assertEquals(0, map.size());

		Assertions.assertNull(map.get(0));
		
		Assertions.assertFalse(map.containsKey(2));
		Assertions.assertFalse(map.containsValue("Daniel"));


		
		/*for(String str : map.values()) {
			System.out.println(str);
		}
		
		for(Integer key : map.keySet()) {
			System.out.println(key);
		}*/
		/*for(Entry<Integer, String> key : map.entrySet()) {
			System.out.println(key);
		}*/
				
		/*for(Entry<Integer, String> key : map.entrySet()) {
			System.out.println(key);
		}*/
		
		/*Iterator<Entry<Integer,String>> iter = map.entrySet().iterator();
		System.out.println(iter.next());*/
	}
	
	@Test
	void test2() {
		HashMap<Integer, String> map= new HashMap<>();
		
		Assertions.assertNotNull(map);
		Assertions.assertEquals(0, map.size());
		
		map.put(1, "Daniel");
		map.put(2, "Yael");
		map.put(3, "Eran");
		map.put(4, "Roi");
		map.put(5, "Inbar");
		map.put(6, "Alex");
		map.put(7, "Mishel");
		map.put(8, "Moti");
		map.put(9, "Eldad");
		
		Assertions.assertEquals(9, map.size());
		Assertions.assertEquals("Yael" ,map.get(2));
		Assertions.assertNull(map.get(12));
		
		HashMap<Integer, String> map2 = new HashMap<>();

		map2.putAll(map);
		
		Assertions.assertEquals(9, map2.size());
		Assertions.assertEquals("Yael" ,map2.get(2));
		Assertions.assertNull(map2.get(12));
	}
	
	@Test
	void testIterator() {
		HashMap<Integer, String> map = new HashMap<>();

		map.put(1, "Daniel");
		map.put(2, "Dani");
		map.put(3, "Dan");
		
		

		Assertions.assertThrows(ConcurrentModificationException.class, () -> {
			Iterator<Entry<Integer, String>> itr = map.entrySet().iterator();
			
			while (itr.hasNext()) {
				itr.next();
				map.put(4, "test"); 
			}
		});
		
		Assertions.assertThrows(ConcurrentModificationException.class, () -> {
			Iterator<Entry<Integer, String>> itr = map.entrySet().iterator();
			
			while (itr.hasNext()) {
				itr.next();
				map.remove(1); 
			}
		});
		
		Assertions.assertThrows(ConcurrentModificationException.class, () -> {
			Iterator<Entry<Integer, String>> itr = map.entrySet().iterator();

			while (itr.hasNext()) {
				itr.next();
				map.put(4, "test"); 
			}
		});
		
		Assertions.assertEquals(3, map.size());


	}

}
