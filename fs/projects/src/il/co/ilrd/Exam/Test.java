package il.co.ilrd.Exam;

public class Test {
	public static void printRevString(String str) {
		char[] arr = str.toCharArray();
		for (int i = arr.length - 1; i >= 0; --i) {
			System.out.print(arr[i]);
		}
	}
	
	public static void printReverse2(String str) {
		System.out.println(new StringBuilder(str).reverse());
	}
	
	public static void printReverse3(String str) {
		for (int i = str.length() - 1; i >= 0; --i) {
			System.out.print(str.charAt(i));
		}
	}


	public static boolean isPolindrome(int num) {
		String numStr = Integer.toString(num);		
		int strLen = numStr.length();
	
		for (int i = 0; i < strLen / 2; ++i) {
			if (numStr.charAt(i) != numStr.charAt(strLen - i - 1)) {
				return false;			
			}
		}

		return true;
	}

	public static int sizeOfMaxISM(int [][]arr) {
		int i = 0;
		int n = arr.length - 1;
		
		for(; i < n; ++i) {
			if(arr[i][i] != 1) {
				break;
			}
			
			for(int j = 0; j < i; ++j) {
				if(arr[j][i] != 0 || arr[i][j] != 0) {
					return i;
				}
			}
		}
		
		return i;
	}
}