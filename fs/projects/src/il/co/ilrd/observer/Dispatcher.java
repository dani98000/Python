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
	}

	public void notify(T data) {
<<<<<<< HEAD
		callbacks.forEach(e->e.update(data));
	}

	public void stop() {
		callbacks.forEach(e->e.stop());
=======
		for(Callback<? super T> subscriber : subscribers) {
			subscriber.update(data);
		}
	}

	public void stop() {
		for(Callback<? super T> subscriber : subscribers) {
			subscriber.stop();
		}
		subscribers.clear();
>>>>>>> f429e462497df75ab2e177f2357d4803bf8474e3
	}
}
