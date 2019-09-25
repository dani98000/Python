package collectionexercises;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.Enumeration;
import java.util.LinkedHashMap;
import java.util.List;
import java.util.Map;
import java.util.Map.Entry;
import java.util.stream.Collectors;

public class Main {
	public static void main(String[] args) {
		// ------------EX1---------------------
		/*int[] arr = { 14, 14, 2, 1, 124, 41241, 0 };
		System.out.println(Arrays.toString(arr));
		List<Integer> list = Arrays.stream(arr).boxed().collect(Collectors.toList());
		Collections.sort(list);
		System.out.println(list.toString());

		// ------------EX2---------------------
		Map<Integer, String> daysOfWeek = new LinkedHashMap<>();
		daysOfWeek.put(1, "Sunday");
		daysOfWeek.put(2, "Monday");
		daysOfWeek.put(3, "Tuesday");
		daysOfWeek.put(4, "Wednesday");
		daysOfWeek.put(5, "Thursday");
		daysOfWeek.put(6, "Friday");
		daysOfWeek.put(7, "Saturday");
		
		for(Entry<Integer, String> e : daysOfWeek.entrySet()) {
			System.out.println(e);
		}
		
		System.out.println();
		
		for(String i : daysOfWeek.values()) {
			System.out.println(i);
		}
		
		//------------EX2---------------------
		DataObject[] dataArr = {new DataObject("Daniel",1,2), new DataObject("Yael",5,18),
						new DataObject("Inbar",1,0), new DataObject("Sandra",1,45)};
		Map<String, Integer> map = new LinkedHashMap<>();
		for(DataObject i : dataArr) {
			map.put(i.code, i.firstValue + i.secondValue);
		}
		
		for(Entry<String, Integer> e : map.entrySet()) {
			System.out.println(e.getKey()+":" + e.getValue());
		}*/
		List<Integer> list = new ArrayList<>();
		list.add(5);
		list.add(2);
		
		System.out.println(list.toString());
		
	}
	
	static class DataObject {
		String code;
		int firstValue;
		int secondValue;
				public DataObject(String code, int firstValue, int secondValue) {
			this.code = code;
			this.firstValue = firstValue;
			this.secondValue = secondValue;
		}
	}
}
