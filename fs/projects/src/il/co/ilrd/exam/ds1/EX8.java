package il.co.ilrd.exam.ds1;

import java.util.HashMap;
import java.util.Iterator;
import java.util.LinkedHashMap;
import java.util.Map.Entry;

public class EX8 {
	HashMap<Integer,Long> uniques = new LinkedHashMap<>();
	HashMap<Long,Integer>map = new HashMap<>();
	int hour = 1;
	
	public void RecieveNum(long N) {
		if(!map.containsKey(N)){
			uniques.put(hour,N);
			map.put(N, hour++);
		}
		else {
			uniques.remove(map.get(N));
		}	
	}
	
	public long FirstNotDuplicateNum() {
		Iterator<Entry<Integer,Long>>iter = uniques.entrySet().iterator();
		return iter.hasNext() ? iter.next().getValue() : 0;
	}
	
	public static void main(String[] args) throws InterruptedException {
		int[] input = {1,2,2,3,3,4,1,1,1,4,4,4,4};
		int i = 0;
		EX8 curr = new EX8();

		while(i < input.length) {
			Thread.sleep(100);
			curr.RecieveNum(input[i++]);
			System.out.print(curr.FirstNotDuplicateNum()+",");
		}
	}
}