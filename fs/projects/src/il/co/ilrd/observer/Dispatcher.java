package il.co.ilrd.observer;

import java.util.LinkedList;
import java.util.List;

public class Dispatcher<T> {
	List<Callback<? super T>> callbacks = new LinkedList<>();
	
	public void subscribe(Callback<? super T> callback) {
		callbacks.add(callback);
		callback.setDispatcher(this);
	}

	public void unsubscribe(Callback<? super T> callback) {
		callbacks.remove(callback);
	}

	public void notify(T data) {
		for(Callback<? super T> callback : callbacks) {
			callback.update(data);
		}
	}

	public void stop() {
		for(Callback<? super T> callback : callbacks) {
			callback.stop();
		}
	}
}
