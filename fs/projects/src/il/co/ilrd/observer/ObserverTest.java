package il.co.ilrd.observer;

import static org.junit.Assert.assertEquals;

import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;

import org.junit.jupiter.api.Test;

import il.co.ilrd.observer.Workout.Exercise;

public class ObserverTest {

	@Test
	void test() {
		List<Client> customers = new LinkedList<>();
		customers.add(new Client("Daniel"));
		customers.add(new Client("Eran"));
		customers.add(new Client("Yael"));
		customers.add(new Client("Sasha"));
		customers.add(new Client("Alex"));
		customers.add(new Client("Roi"));

		Gym countryClubArad = new Gym();
		List<Exercise>upperBodyExercises = new ArrayList<>();
		upperBodyExercises.add(new Exercise("Bench Press",5,5,120));
		upperBodyExercises.add(new Exercise("Barbell Rows",3,8,120));
		upperBodyExercises.add(new Exercise("Military Press",3,10,90));
		upperBodyExercises.add(new Exercise("Hammer Curls",3,12,60));
		upperBodyExercises.add(new Exercise("Tricep Rope Extensions",3,15,60));
		
		Workout upperBodyWorkout = new Workout(upperBodyExercises, "upperBodyWorkout");
		countryClubArad.addWorkouts(upperBodyWorkout);
		for(Client client : customers) {
			client.register(countryClubArad);
		}

		countryClubArad.notify(upperBodyWorkout);
        
		for(Client client : customers) {
			assertEquals(1, client.getcountOpen());
		}
		
		countryClubArad.stop();
		
		for(Client client : customers) {
			assertEquals(1, client.getcountClose());
		}
		
		assertEquals(6, countryClubArad.getNumMembers());
		
		for(Client client : customers) {
			client.unregister(countryClubArad);
		}
		
		assertEquals(0, countryClubArad.getNumMembers());
		
		for(Client client : customers) {
			assertEquals(1, client.getcountClose());
		}
	}

}

class Workout {
	private List<Exercise> exercises = new ArrayList<>();
	private String name;
	
	public Workout(List<Exercise> exercises, String name) {
		this.exercises = exercises;
		this.name = name;
	}
	
	public List<Exercise> getWorkout(){
		return exercises;
	}
	
	static class Exercise {
		private String name;
		private int numSets;
		private int numReps;
		private int restTime;
		
		public Exercise(String name, int numSets, int numReps, int restTime) {
			this.name = name;
			this.numSets = numSets;
			this.numReps = numReps;
			this.restTime = restTime;
		}

		public String getName() {
			return name;
		}

		public int getNumSets() {
			return numSets;
		}

		public int getNumReps() {
			return numReps;
		}

		public int getRestTime() {
			return restTime;
		}
	}
}

class UpperBodyWorkout extends Workout{

	public UpperBodyWorkout(List<Exercise> exercises, String name) {
		super(exercises, name);
	}
}

class LowerBodyWorkout extends Workout{

	public LowerBodyWorkout(List<Exercise> exercises, String name) {
		super(exercises, name);
	}
}

class Client{
	private String name;
	private Callback<Workout> callback;
	private int countClose = 0;
	private int countOpen = 0;
	
	public Client(String name) {
		this.name = name;
		this.callback = new Callback<Workout>(this::workout, this::gymClosed);
	}
	
	private void workout(Workout workout) {
		++countOpen;
		System.out.println("Hello " + name + " this is your workout!");
		for(Exercise exercise : workout.getWorkout()) {
			System.out.print(exercise.getName() + " : ");
			System.out.println(exercise.getNumSets() + " sets of " + exercise.getNumReps() + " reps with " +
			exercise.getRestTime() + " seconds rest.");
		}
		System.out.println("--------------------------------------------------------------------------");
	}
	
	private void gymClosed() {
		++countClose;
		System.out.println("Sorry " + name + "Gym is closed for today, Come back tomorrow!");
	}
	
	public Callback<Workout> getCallback(){
		return callback;
	}
	
	public void register(Gym gym) {
		gym.subscribe(callback);		
	}
	
	public void unregister(Gym gym) {
		gym.unsubscribe(callback);
	}
	
	int getcountClose() {
		return countClose;
	}
	
	int getcountOpen() {
		return countOpen;
	}
}

class Gym {
	private int numMembers;
	private List<Client> clients = new ArrayList<>();
	private List<Workout> availableWorkouts = new ArrayList<>();
	private Dispatcher<Workout> dispatcher = new Dispatcher<>();
	
	public void subscribe(Callback<Workout> callback) {
		dispatcher.subscribe(callback);
		++numMembers;
	}
	
	public void unsubscribe(Callback<Workout> callback) {
		--numMembers;
		dispatcher.unsubscribe(callback);
	}
	
	public void stop() {
		dispatcher.stop();
	}
	
	public void notify(Workout data) {
		dispatcher.notify(data);		
	}
	
	public int getNumMembers() {
		return numMembers;
	}
	
	public void addWorkouts(Workout workout) {
		availableWorkouts.add(workout);
	}
}