
public class Test {
	public static void main(String[] args) {
		SinglyLinkedList list = new SinglyLinkedList();
		list.pushFront(5);
		list.pushFront(6);
		System.out.println(list.find(5).next());
		System.out.println(list.find(6).next());
		System.out.println(list.find(8) == null);
	}
}
