import java.util.List;
import java.util.ArrayList;

public class ex4{
	public static void main(String[] args){
		List<int[]> myList = new ArrayList<int[]>();
		int listSize = myList.size();
		for(int i = 0; i < 100000; ++i)
		{
			int[] intArray = new int[100000];
			myList.add(intArray);
		}

		Runtime run = Runtime.getRuntime(); 
        System.out.println("" + run.freeMemory());
	}	
}