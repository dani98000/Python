package InterviewAssigment;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.RandomAccessFile;
import java.time.Instant;
import java.time.ZoneOffset;
import java.time.ZonedDateTime;
import java.util.Date;
import java.util.HashMap;
import java.util.Map;

import javax.xml.bind.annotation.adapters.HexBinaryAdapter;

public class ParseContactsFromFile {
	private static final String FIRST_NAME_CODE = "86B7";
	private static final String LAST_NAME_CODE = "9E60";
	private static final String PHONE_NUMBER_CODE = "5159";
	private static final String DATE_CODE = "D812";
	private static final int SIZE_OF_KEY = 4;
	private static final int SIZE_OF_DATA_TYPE = 4;
	private static final int DATA_LEN = 5;
	private final BufferedReader reader;
	private final Map<String, ContactInfo> contacts = new HashMap<>();
	
	public ParseContactsFromFile(String fileName) throws FileNotFoundException {
		reader = new BufferedReader(new FileReader(fileName));
	}
	
	public void decryptContacts() throws IOException {
		String line;
		
		while((line = reader.readLine()) != null) {
			int i = 0;
			String dataType = line.substring(i, i + SIZE_OF_DATA_TYPE);
			i += SIZE_OF_DATA_TYPE;
			
			while(i < line.length()) {
				String key = line.substring(i, i + SIZE_OF_KEY);
				i += SIZE_OF_KEY;
				int numToRead = Integer.parseInt(line.substring(i, i + DATA_LEN), 16);
				i += DATA_LEN;
				String data = line.substring(i, i + numToRead);
				updateContact(dataType, data, key);
				i += numToRead;
			}
		}
		displayContacts();
	}
	
	private void displayContacts() {
		for(ContactInfo contact : contacts.values()) {
			contact.displayContact();
		}
	}
	
	public void updateContact(String dataType, String data, String contactKey) {
		if(!contacts.containsKey(contactKey)) {
			contacts.put(contactKey, new ContactInfo());
		}
		
		switch(dataType) {
			case FIRST_NAME_CODE :
				contacts.get(contactKey).setFirstName(data);					
				break;
			case LAST_NAME_CODE :
				contacts.get(contactKey).setLastName(data);					
				break;
			case PHONE_NUMBER_CODE : 
				contacts.get(contactKey).setPhoneNumber(data);
				break;
			case DATE_CODE :
				long timestamp = Long.parseLong(data);
				Date expiry = new Date(timestamp * 1000);
				contacts.get(contactKey).setDate(expiry);
				break;
		}
	}
	
	private static class ContactInfo {
		private String firstName, lastName, phoneNumber;
		private Date date;
				
		public void setFirstName(String firstName) {
			this.firstName = firstName;
		}
		
		public void setLastName(String lastName) {
			this.lastName = lastName;
		}
	
		public void setPhoneNumber(String phoneNumber) {
			this.phoneNumber = phoneNumber;
		}
		
		public void setDate(Date date) {
			this.date = date;
		}
		
		private void displayContact() {
			System.out.println("First Name: " + firstName);
			System.out.println("Last Name: " + lastName);
			System.out.println("Phone Number : " + phoneNumber);
			System.out.println("Date : " + date);
			System.out.println("---------------------------------");
		}
	}
}
