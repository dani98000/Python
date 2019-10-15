package il.co.ilrd.observer;

import java.util.LinkedList;
import java.util.List;

public class Dispatcher<T> {
	private List<Callback<? super T>> subscribers = new LinkedList<>();
	
	public void subscribe(Callback<? super T> subscriber) {
		subscribers.add(subscriber);
		subscriber.setDispatcher(this);
	}

	public void unsubscribe(Callback<? super T> subscriber) {
		subscribers.remove(subscriber);
		subscriber.setDispatcher(null);
	}

	public void notify(T data) {
		subscribers.forEach(e->e.update(data));
	}

	public void stop() {
		subscribers.forEach(e->e.stop());
		subscribers.clear();
	}
}