package il.co.ilrd.Exam;

public class Main {
	public static void main(String[] args) {
		String str = "daniel";
		Test.printRevString(str);
		System.out.println("");
		int num = 21;
		System.out.println(Test.isPolindrome(num));
		
		int [][]arr1 = 
		{
			{1,2,0,4},
			{3,1,0,4},
			{0,0,1,7},
			{7,9,9,9}
		};
		
		int [][]arr2 = 
		{
			{1,0,7,4},
			{0,1,0,4},
			{4,0,1,7},
			{7,9,9,9}
		};
		
		int [][]arr3 = 
		{
			{1,0,0,4},
			{0,1,0,4},
			{0,0,1,7},
			{7,9,9,9}
		};
		
		int size1 = Test.sizeOfMaxISM(arr1);
		int size2 = Test.sizeOfMaxISM(arr2);
		int size3 = Test.sizeOfMaxISM(arr3);

		
		System.out.println(size1);
		System.out.println(size2);
		System.out.println(size3);
	}
}
