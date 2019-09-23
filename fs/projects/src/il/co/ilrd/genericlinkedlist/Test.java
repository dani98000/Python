package il.co.ilrd.genericlinkedlist;

import java.util.Iterator;

public class Test {
	public static void main(String[] args) {
		GenericLinkedList<Integer> list = new GenericLinkedList<>();
		list.PushFront(1);
		list.PushFront(2);
		list.PushFront(3);
		list.PushFront(4);
		list.PushFront(5);
		
		//System.out.println(list.Size());
		list.DisplayList();
		GenericLinkedList.Reverse(list);
		list.DisplayList();
		Iterator a = list.Find(5);
		System.out.println(a.next());
	}
}
