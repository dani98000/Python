package il.co.ilrd.exam.ds1;

import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertTrue;
import static org.junit.jupiter.api.Assertions.assertArrayEquals;

import org.junit.Test;

public class TestExam {
	
	@Test
	public void TestArrayShift() {
		char[] arr = {'H','e','l','l','o'};
		char[] expected = {'l','o','H','e','l'};

		Ex1.ArrayShift(arr, 2);
		assertArrayEquals(expected, arr);
	}
	
	@Test
	public void TestPushZerosToEnd() {
		int[] arr = {1,9,8,4,0,0,2,7,0,6,0};
		int[] expected = {1,9,8,4,2,7,6,0,0,0,0};


		Ex1.PushZerosToEnd(arr);
		assertArrayEquals(expected, arr);
	}
	
	@Test
	public void TestSinglyLinkedList1() {
    	SinglyLinkedList sll1= new SinglyLinkedList();
    	sll1.addNode(1);
    	sll1.addNode(2);
    	sll1.addNode(3);
    	sll1.addNode(4);
    	sll1.addNode(5);
    	
    	sll1.createLoop(2);
    	assertTrue(sll1.HasLoop());
    	
    	sll1.OpenLoop();
    	assertFalse(sll1.HasLoop());
    	
    	SinglyLinkedList sll2 = new SinglyLinkedList();
    	sll2.addNode(6);
    	sll2.addNode(7);
    	sll2.addNode(8);
    	
    	SinglyLinkedList.CreateIntersecedLists(sll1, sll2);

    	assertTrue(SinglyLinkedList.hasIntersection(sll1, sll2));
    	SinglyLinkedList.seperateIntersectedLoops(sll1, sll2);
    	assertFalse(SinglyLinkedList.hasIntersection(sll1, sll2));    	
	}

}