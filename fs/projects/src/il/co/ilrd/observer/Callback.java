package il.co.ilrd.observer;

import java.util.function.Consumer;

public class Callback<T>{
	Consumer<T> onUpdate;
	Worker onStop;
	private Dispatcher<? extends T> dispatcher;
	
	public Callback(Consumer<T> onUpdate, Worker onStop) {
		this.onUpdate = onUpdate;
		this.onStop = onStop;
	}

	void setDispatcher(Dispatcher<? extends T> dispatcher) { this.dispatcher = dispatcher; }
	void update(T data) { onUpdate.accept(data); }
	void stop() { onStop.doWork(); }
	void unsubscribe() { dispatcher.unsubscribe(this); }
}
