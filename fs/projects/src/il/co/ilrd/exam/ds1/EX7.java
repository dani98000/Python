package il.co.ilrd.exam.ds1;

public class EX7 {
	public static void PrintReverseString(String str) {
		if(!str.isEmpty()) {
			PrintReverseString(str.substring(1, str.length()));
			System.out.print(str.charAt(0));
		}
	}
	
	public static void RecStringPermutations(String str, int l, int r) {
		if(l == r) {
			System.out.println(str);
		}else {
			for(int i = l; i <= r; ++i) {
				str = swap(str,l,i);
				RecStringPermutations(str, l + 1, r);
				str = swap(str,l,i);
			}
		}
	}
	
	public static void StringPermutations(String str) {
		RecStringPermutations(str, 0, str.length() - 1);
	}
	
    private static String swap(String str, int i, int j) { 
        char temp; 
        char[] charArray = str.toCharArray(); 
        temp = charArray[i] ; 
        charArray[i] = charArray[j]; 
        charArray[j] = temp; 
        return String.valueOf(charArray); 
    } 
}
