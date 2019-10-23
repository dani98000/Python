package crud;

import java.util.Collection;
import java.util.function.Consumer;
import java.util.function.Predicate;

public interface Crud <E extends Cloneable> {
	
	/**
	 * Creates a new entry in storage.
	 * Returns Unique ID.
	 */
	public int Create(E entry);
	
	/**
	 * Returns a copy of a single entry corresponding 
     * to the given id, null otherwise.
	 */
	public E Read(int id);
	
	/**
	 * returns a Collection of copies of all read elements.
	 */
	public Collection<E> Read(Predicate<E> shouldRead);
	
	/** 
	 * Returns if the item was updated
	 */
	public boolean Update(int id, Predicate<E> shouldUpdate);
	
	/**
	 * returns a collection of all the 
	 * items that were updated
	 */
	public Collection<E> Update(Predicate<E> shouldUpdate, Consumer<E> updateFunction);
	
	/**
	 * Deletes the given ID
	 */
	public void Delete(int id);
}
