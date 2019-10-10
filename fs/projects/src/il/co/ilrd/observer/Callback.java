package il.co.ilrd.observer;

import java.util.function.Consumer;

public class Callback<T>{
	private Consumer<T> onUpdate;
	private Worker onStop;
	private Dispatcher<? extends T> dispatcher;
	
	public Callback(Consumer<T> onUpdate, Worker onStop) {
		this.onUpdate = onUpdate;
		this.onStop = onStop;
	}

	void setDispatcher(Dispatcher<? extends T> dispatcher) {
<<<<<<< HEAD
		this.dispatcher = dispatcher; 
	}
	
	void update(T data) { 
		onUpdate.accept(data);
	}
	
	void stop() {
		onStop.doWork(); 
		dispatcher = null;
=======
		this.dispatcher = dispatcher;
	}
	
	void update(T data) { 
		onUpdate.accept(data); 
	}
	
	void stop() { 
		onStop.doWork();
		setDispatcher(null);
>>>>>>> f429e462497df75ab2e177f2357d4803bf8474e3
	}
	
	void unsubscribe() { 
		dispatcher.unsubscribe(this); 
<<<<<<< HEAD
		dispatcher = null;
=======
		setDispatcher(null);
>>>>>>> f429e462497df75ab2e177f2357d4803bf8474e3
	}
}
