package InterviewAssigment;

import java.io.FileNotFoundException;
import java.io.IOException;

public class Main {
	public static void main(String[] args) throws IOException {
		ParseContactsFromFile parser = new ParseContactsFromFile("/home/dani98000/ex_v8.txt");
		parser.decryptContacts();
	}
}
