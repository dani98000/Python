package il.co.ilrd.exam.ds1;

public class Ex2 {
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
