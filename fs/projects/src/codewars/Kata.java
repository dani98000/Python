package codewars;

import java.util.HashMap;
import java.util.LinkedHashMap;
import java.util.Map;

public class Kata {
		public static int josephusSurvivor(final int n, final int k) {
			HashMap<Integer, Integer> map = new LinkedHashMap<>();
            if(map.containsKey(nums[i][j])){

			for(int i = 0; i < n; ++i) {
				map.put(i, (i + k) % n);
			}
			
			while(map.size() != 1) {
				int i = 0;
				map.remove(i);
				map.replace(i, (i + k) % n);
				i = (i + 3) % k;
			}
			
			return map.entrySet().iterator().next().getKey();
		}  

		public static void main(String[] args) {
			System.out.println(Kata.josephusSurvivor(7,3));
		}
}
