package il.co.ilrd.exam.ds1;

import java.util.LinkedList;
import java.util.List;
import java.util.Queue;

public class EX8 {
	Queue<Long> uniquesQueue = new LinkedList<>();
	long[] g_lut = new long[10000];
		
	public void RecieveNum(long N) {
		
		if(g_lut[(int)N] == 0){
			uniquesQueue.add(N);
			++g_lut[(int)N];
		}
		else {
			uniquesQueue.remove((Object)N);				
			++g_lut[(int) N];
		}	
	}
	
	public long FirstNotDuplicateNum() {
		if(this.uniquesQueue.isEmpty()) {
			return 0;
		}
		if(g_lut[this.uniquesQueue.peek().intValue()] == 1) {
			return this.uniquesQueue.peek();
		}else {
			return 0;
		}
	}
	
	public static void main(String[] args) throws InterruptedException {
		int[] input = {1,2,2,3,3,4,1,1,1};
		int i = 0;
		EX8 curr = new EX8();

		while(i < input.length) {
			Thread.sleep(1000);
			curr.RecieveNum(input[i++]);
			System.out.println(curr.FirstNotDuplicateNum());
		}
	}
}
