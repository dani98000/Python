package il.co.ilrd.observer;

import static org.junit.jupiter.api.Assertions.*;

import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;

import org.junit.jupiter.api.Test;

import il.co.ilrd.observer.Client.workouts;
import il.co.ilrd.observer.ConsumerTest.Observer;
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
			client.register(countryClubArad, workouts.upperBody);
		}
		
		for(Client client : customers) {
			countryClubArad.notify("New Workout EveryBody!!!");
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
	private Callback<String> callback;
	Workout workout;
	enum workouts{
		upperBody (0), lowerBody (1);
		private workouts(int index) {}
	};

	public Client(String name) {
		this.name = name;
		this.callback = new Callback<String>(this::workout, this::gymClosed);
	}
	
	private void workout(String str) {
		System.out.println(str + "\n\n");
		System.out.println("Hello " + name + " this is your workout!");
		for(Exercise exercise : workout.getWorkout()) {
			System.out.print(exercise.getName() + " : ");
			System.out.println(exercise.getNumSets() + " sets of " + exercise.getNumReps() + " reps with " +
			exercise.getRestTime() + " seconds rest.");
		}
		System.out.println("--------------------------------------------------------------------------");
	}
	
	private void gymClosed() {
		System.out.println("Sorry " + name + "Gym is closed for today, Come back tomorrow!");
	}
	
	public Callback<String> getCallback(){
		return callback;
	}
	
	public void register(Gym gym, workouts bodyPart) {
		gym.subscribe(callback);
		if(bodyPart.equals(workouts.upperBody)) {
			workout = gym.getAvailableWorkouts().get(workouts.upperBody.ordinal());			
		}else {
			workout = gym.getAvailableWorkouts().get(workouts.lowerBody.ordinal());			
		}
		
	}
	
	public void unregister(Gym gym) {
		gym.unsubscribe(callback);
	}
}

class Gym {
	private int numMembers;
	private List<Client> clients = new ArrayList<>();
	private List<Workout> availableWorkouts = new ArrayList<>();
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
	
	public void addWorkouts(Workout workout) {
		availableWorkouts.add(workout);
	}
	
	public List<Workout> getAvailableWorkouts(){
		return availableWorkouts;
	}
}