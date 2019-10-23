package il.co.ilrd.crud;

import java.io.Serializable;

public interface Crud <E extends Serializable, K extends Serializable> extends AutoCloseable{
	
	/**
	 * Creates a new entry in storage.
	 * Returns Unique ID.
	 */
	public K Create(E entry);
	
	/**
	 * Returns a copy of a single entry corresponding 
     * to the given id, null otherwise.
	 */
	public E Read(K id);
	
	/** 
	 * Returns if the item was updated
	 */
	public void Update(K id, E newData);
	
	/**
	 * Deletes the given ID
	 */
	public void Delete(K id);
}
