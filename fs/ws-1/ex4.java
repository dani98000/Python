import java.util.List;
import java.util.ArrayList;
import java.lang.ref.WeakReference;

public class ex4{
	public static void main(String[] args){
	
		List<WeakReference<int[]>> myList = new ArrayList<>();
		
		for(int i = 0; i < 100000; ++i)
		{
			myList.add(new WeakReference<int[]>(new int[100000]));
   			try
			{
				Thread.sleep(1);
			}
			catch(InterruptedException e)
			{
				System.out.println(e);
			}  	
		}

		Runtime run = Runtime.getRuntime(); 
        System.out.println("" + run.freeMemory());
	}	
}
