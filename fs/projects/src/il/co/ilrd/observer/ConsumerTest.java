package il.co.ilrd.observer;

import java.util.LinkedList;
import java.util.List;

public class ConsumerTest {
	class Observer{
		private String name;
		private Callback<String> callback;
	
		public Observer(String name) {
			this.name = name;
			this.callback = new Callback<String>(this::workout, this::gymClosed);
		}
		
		private void workout(String workoutInfo) {
			System.out.println("Hello " + name + "! : " + workoutInfo);
		}
		
		private void gymClosed() {
			System.out.println("Sorry " + name + "Gym is closed for today, Come back tomorrow!");
		}
		
		public Callback<String> getCallback(){
			return callback;
		}
		
		public void register(Gym gym) {
			gym.subscribe(callback);
		}
		
		public void unregister(Gym gym) {
			gym.unsubscribe(callback);
		}
	}
	
	class Gym {
		private int numMembers;
		private Dispatcher<String> dispatcher = new Dispatcher<>();
		
		public void subscribe(Callback<String> callback) {
			dispatcher.subscribe(callback);
			++numMembers;
		}
		
		public void unsubscribe(Callback<String> callback) {
			--numMembers;
			dispatcher.unsubscribe(callback);
		}
		
		public void stop() {
			dispatcher.stop();
		}
		
		public void notify(String data) {
			dispatcher.notify(data);		
		}
		
		public int getNumMembers() {
			return numMembers;
		}
	}
	
	public static void main(String[] args) {
		List<Observer> customers = new LinkedList<>();
		customers.add((new ConsumerTest()).new Observer("Daniel"));
		customers.add((new ConsumerTest()).new Observer("Eran"));
		customers.add((new ConsumerTest()).new Observer("Yael"));
		customers.add((new ConsumerTest()).new Observer("Roi"));
		customers.add((new ConsumerTest()).new Observer("Alex"));
		customers.add((new ConsumerTest()).new Observer("Sasha"));

		ConsumerTest.Gym countryClubArad = (new ConsumerTest()).new Gym();
		
		for(Observer customer : customers) {
			customer.register(countryClubArad);
		}
		              
		countryClubArad.notify("squats 5*5");
		
		for(Observer customer : customers) {
			customer.unregister(countryClubArad);		
		}
		
		countryClubArad.notify("Bench Press 5*5");
		
		for(Observer customer : customers) {
			customer.register(countryClubArad);
		}
		
		countryClubArad.stop();
		
		for(Observer customer : customers) {
			customer.getCallback().unsubscribe();
		}
		
		System.out.println(countryClubArad.getNumMembers());
	}
}
