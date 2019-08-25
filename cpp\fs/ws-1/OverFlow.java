
import java.lang.*;

class Overflow {
	private int x = 0;

	void overflow() {
		
		//if (this.MAX <= this.x)
		//	return ;
		System.out.println(x);
		++this.x;

		overflow();
    }
    
	public static void main(String[] args) {
		
		Overflow.overflow();
	}
}

