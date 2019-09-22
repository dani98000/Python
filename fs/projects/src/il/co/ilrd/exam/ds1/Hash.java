package il.co.ilrd.exam.ds1;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.HashMap;
import java.util.ArrayList;
import java.util.Arrays;

public class Hash {	     
	static HashMap<Integer, ArrayList<String>> dictionary;

	static void listAnagramsFor(String word) throws IOException {
		FillMap();
		int key = getKey(word);
		if (dictionary.containsKey(key)) {
			ArrayList<String> list = dictionary.get(key);

			for (String item : list) {
				System.out.println(item);
			}
		}
	}

	public static int getKey(String str) {
		char[] charArray = str.toCharArray();
		Arrays.sort(charArray);

		return String.copyValueOf(charArray).hashCode();
	}

	private static void FillMap() throws IOException {
		BufferedReader reader = new BufferedReader(new FileReader("/usr/share/dict/words"));
		dictionary = new HashMap<>(); 

		while (true) {
			String line = reader.readLine();
			if (line == null) {
				break;
			}

			int key = getKey(line);

			if (dictionary.containsKey(key)) {
				dictionary.get(key).add(line);
			} else {
				ArrayList<String> list = new ArrayList<>();
				list.add(line);
				dictionary.put(key, list);
			}
		}

		reader.close();
	}
	
	public static void PrintMissingElements(int[] arr, int low, int high){
		int[] lut = new int[high-low + 1];
		
		for(int i = 0; i < arr.length; ++i) {
			lut[arr[i] - low] = 1;
		}

		for(int i = 0; i < lut.length; ++i) {
			if(lut[i] != 1) {
				System.out.print(i + low + ",");
			}
		}
	}
}
