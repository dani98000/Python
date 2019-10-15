package il.co.ilrd.observer;

import java.util.function.Consumer;

public class Callback<T>{
	private Consumer<T> onUpdate;
	private Worker onStop;
	private Dispatcher<? extends T> dispatcher;
	
	public Callback(Consumer<T> onUpdate, Worker onStop) {
		if (onUpdate == null) {
			throw new IllegalArgumentException();
		}

		this.onUpdate = onUpdate;
		this.onStop = onStop;
	}

	void setDispatcher(Dispatcher<? extends T> dispatcher) {
		this.dispatcher = dispatcher; 
	}
	
	void update(T data) { 
		onUpdate.accept(data);
	}
	
	void stop() {
		if (onStop == null) {
			return;
		}
		onStop.doWork(); 
	}
	
	void unsubscribe() { 
		dispatcher.unsubscribe(this); 
		setDispatcher(null);
	}
}
