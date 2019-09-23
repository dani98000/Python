package il.co.ilrd.genericlinkedlist;

import java.util.Iterator;

public class GenericLinkedList <T> implements Iterable<T>{
	public void PushFront(T data) {}
	
	public T PopFront() {
		return null;
	}
	
	public int Size() {
		return 0;
	}
	
	public boolean IsEmpty(){
		return false;
	}
	
	public static <T> GenericLinkedList<T> Reverse(GenericLinkedList<T>list){
		return list;
	}
	
	public static <T> GenericLinkedList<T> Merge(GenericLinkedList<T>list1, GenericLinkedList<T>list2){
		return list2;
	}
	
	@Override
	public Iterator<T> iterator(){
		return null;}
	
	private class IteratorImpel<T> implements Iterator<T>{

		@Override
		public boolean hasNext() {
			// TODO Auto-generated method stub
			return false;
		}

		@Override
		public T next() {
			// TODO Auto-generated method stub
			return null;
		}
	
	}
}
