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
		for(Callback<? super T> subscriber : subscribers) {
			subscriber.update(data);
		}
	}

	public void stop() {
		for(Callback<? super T> subscriber : subscribers) {
			subscriber.stop();
		}
		subscribers.clear();
	}
}
