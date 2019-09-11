package il.co.ilrd.reflection;

public class Foo {		 
    private int age;
    public int id;
 
    public Foo(int age, int id) {
    	this.age = age;
    	this.id = id;
    }

	public int getAge() {
		return age;
	}

	public void setAge(int age) {
		this.age = age;
	}

	public int getId() {
		return id;
	}

	public void setId(int id) {
		this.id = id;
	}
}
