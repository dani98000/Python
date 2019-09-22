package il.co.ilrd.exam.ds1;

public class CircularShift {
	public static void ArrayShift(char[] arr, int n) {
		 int gcd = GCD(arr.length ,n);
		 char temp;
		 
		 for(int i = 0,j, next; i < gcd; ++i) {;
			 temp = arr[i];
			 j = i;
			 
			 while(true) {
				 next = (j + n) % arr.length;
				 
				 if(next == i) {
					 break;
				 }
				 
				 arr[j] = arr[next];
				 j = next;
			 }
			 arr[j] = temp;
		 }
	}
	
	public static int GCD(int a, int b){
		if(b == 0) {
			return a;
		} else {
			return GCD(b, a % b);
		}
		
	}
}
