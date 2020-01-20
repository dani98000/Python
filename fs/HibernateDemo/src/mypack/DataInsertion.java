package mypack;

import org.hibernate.Session;
import org.hibernate.SessionFactory;
import org.hibernate.Transaction;
import org.hibernate.cfg.Configuration;

public class DataInsertion {

	public static void main(String[] args) {
		DataInsertion.insertInfo();
	}
	
	public static void insertInfo() {
		Configuration con = new Configuration();
		con.configure("hibernate.cfg.xml");
		SessionFactory sf = con.buildSessionFactory();
		Session session = sf.openSession();
		DataProvider provider = new DataProvider();
		
		provider.setName("Daniel");
		provider.setAge(22);
		provider.setGender("Male");
		
		Transaction transaction = session.beginTransaction();
		session.save(provider);
		System.out.println("Customer saved successfully!!!");
		transaction.commit();
		session.close();
		sf.close();
	}
}
