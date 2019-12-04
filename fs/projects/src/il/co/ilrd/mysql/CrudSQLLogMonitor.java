package il.co.ilrd.mysql;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.concurrent.atomic.AtomicInteger;

import il.co.ilrd.crud.CRUD;

public class CrudSQLLogMonitor implements CRUD<String, Integer>{
	private AtomicInteger id;
	private String tableName;
	private MySQLUtility sqlUtil;
	
	public CrudSQLLogMonitor(String DBName, String tableName, String username, String password) throws SQLException {
		this.tableName = tableName;
		id = new AtomicInteger(0);
		sqlUtil = new MySQLUtility(DBName, username, password);
		updateID();
		sqlUtil.createTable(tableName, "id INT PRIMARY KEY, message TEXT");
	}
	
	private void updateID() throws SQLException {
		if(sqlUtil.checkIfTableExists(tableName)) {
			ResultSet rs = sqlUtil.execute("SELECT MAX(id) from " + tableName);
			if(rs.next()){
				id.set(rs.getInt(1) + 1);
			}	
		}
	}
	
	@Override
	public Integer create(String str) {
		str = str.replaceAll("\"", "");
		int messageID = id.getAndIncrement();
		String query = "INSERT INTO " + tableName + "(id, message) "
					 + "VALUES (" + messageID + ",\"" + str + "\")";
		try {
			sqlUtil.executeModify(query);
		} catch (SQLException e) {
			e.printStackTrace();
		}
		
		return messageID;
	}
	
	@Override
	public String read(Integer id) {
		ResultSet rs;
		String ret = null;
		String query = "SELECT message FROM " + tableName + " WHERE id = " + id;
		System.out.println(query);
		try {
			rs = sqlUtil.execute(query);
			if(rs.next()){
				   ret = rs.getString(1);
			}		
		} catch (SQLException e) {
			e.printStackTrace();
		}
		
		return ret;
	}
	
	@Override
	public void update(Integer id, String str) {
		String query = "UPDATE "+ tableName + "SET id =  " + id + ", message = " + str + "\"";
		try {
			sqlUtil.executeModify(query);
		} catch (SQLException e) {
			e.printStackTrace();
		}		
	}
	
	@Override
	public void delete(Integer id) {
		String query = "DELETE FROM "+ tableName + " WHERE id = " + id;
		try {
			sqlUtil.executeModify(query);
		} catch (SQLException e) {
			e.printStackTrace();
		}
	}

	@Override
	public void close() throws Exception {
		sqlUtil.close();
	}
}
