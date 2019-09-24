package il.co.ilrd.test;

public class Foo {
	public static void main(String[] args) {
		Foo.FooReference<Integer> integer = new Foo.FooReference<>(5);
		System.out.println(integer.get());
		System.out.println(integer.getClass().getName());
		
		Foo.FooReference<String> string = new Foo.FooReference<>("Daniel");
		System.out.println(string.get());
		System.out.println(string.getClass().getName());	
	}
	
	public static class FooReference <T>{
	    private T t;
	    
	    public FooReference(T t) {
	    	this.t = t;
	    }
		
		public T get(){
			return t;
		}
		
		public void set(T t) {
			this.t = t;
		}
	}

	
	public static <T> void printArray(T[] arr) {
		for(T element : arr) {
			System.out.print(element+",");
		}
		System.out.println();
	}
}
