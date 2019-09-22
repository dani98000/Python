package il.co.ilrd.exam.ds1;

public class Ex1 {
	public static void ArrayShift(char[] arr, int n) {		
		ReverseString(arr, 0, arr.length - 1);
		ReverseString(arr,0,n-1);
		ReverseString(arr,n,arr.length-1);
	}
	
	private static void ReverseString(char[] arr, int from, int to) {
        char temp  = 0;
        int j = 0;
        
		for(int i = from; i < to; ++i, ++j) {
        	if(i == to - j) {
        		break;
        	}
			temp  = arr[i];
        	arr[i] = arr[to - j];
        	arr[to - j] = temp;
		}
	}
	
	public static void PushZerosToEnd(int[] arr) {
		int temp = 0;
		int runnerIndex = 0;
		int flag = 0;
		
		for(int i = 0; i < arr.length; ++i) {
			runnerIndex = i;
			if(arr[i] == 0) {
				while(arr[runnerIndex] == 0 && flag != 1) {
					++runnerIndex;
					if(runnerIndex >= arr.length - 1) {
						flag = 1;
					}
				}
				
				temp = arr[i];
				arr[i] = arr[runnerIndex];
				arr[runnerIndex] = temp;
			}			
		}
	}
}
