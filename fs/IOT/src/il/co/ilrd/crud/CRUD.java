package il.co.ilrd.crud;

import java.io.Serializable;

public interface CRUD <E extends Serializable, K extends Serializable> extends AutoCloseable{
	
	/**
	 * Creates a new entry in storage.
	 * Returns Unique ID.
	 */
	public K create(E entry);
	
	/**
	 * Returns a copy of a single entry corresponding 
     * to the given id, null otherwise.
	 */
	public E read(K id);
	
	/** 
	 * Returns if the item was updated
	 */
	public void update(K id, E newData);
	
	/**
	 * Deletes the given ID
	 */
	public void delete(K id);
}
