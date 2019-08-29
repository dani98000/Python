import static org.junit.jupiter.api.Assertions.*;
import org.junit.jupiter.api.DisplayName;
import org.junit.jupiter.api.Test;

public class SLLTest {
	
	@Test
	@DisplayName("😱")
			
	void test1() {
		int res = 0;
		SinglyLinkedList list = new SinglyLinkedList();

		//test1
		list.pushFront(1);
		list.pushFront(2);
		list.pushFront(3);
		
		res = list.getSize();
		assertEquals(res, 3);
		
		//test2
		list.popFront();
		res = list.getSize();
		assertEquals(res, 2);
	
		//test3
		res = (Integer)(list.begin().next());
		assertEquals(res, 2);
		
		//test4
		assertEquals(list.isEmpty(), false);
	}


}
