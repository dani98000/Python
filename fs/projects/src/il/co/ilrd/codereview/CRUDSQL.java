package il.co.ilrd.codereview;

import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.concurrent.atomic.AtomicInteger;

import il.co.ilrd.crud.CRUD;

public class CRUDSQL implements CRUD<String, Integer> {
	private MySQLUtility sqlUtil;
	private AtomicInteger lineID;
	private static final String tableName = "LogMonitor";
	private static final String LINE = "lineID";

	public CRUDSQL(String dataBaseURL, String userName, String password) throws SQLException {
		sqlUtil = new MySQLUtility(dataBaseURL,userName, password);
		String query = new StringBuilder("SHOW TABLES LIKE \'" + tableName + "\'").toString();
		int numRows = sqlUtil.update(query);
		
		if(0 == numRows) {
			sqlUtil.createTable(tableName);
			lineID = new AtomicInteger(0);
		} else {
			query = new StringBuilder("Select max(lineID) lineID FROM " + tableName).toString();
			ResultSet result = sqlUtil.executeQuery(query);
			result.first();
			lineID = new AtomicInteger(result.getInt(LINE) + 1);
		}
		
	}
	
	@Override
	public void close() throws Exception {
		sqlUtil.close();
		
	}

	@Override
	public Integer create(String entry) {
		Integer id = lineID.getAndIncrement();
		entry = entry.replaceAll("'", "''");
		String query = new StringBuilder("INSERT INTO " + tableName + " VALUES (" + id + ", \'" + entry + "\');").toString();
		System.out.println("INSERT INTO " + tableName + " VALUES (" + id + ", \'" + entry + "\');");
		try {
			sqlUtil.insert(query.toString());
		} catch (SQLException e) {
			e.printStackTrace();
		}
		
		return id;
	}

	@Override
	public String read(Integer key) {
		String query = new StringBuilder("SELECT " + LINE +", Text FROM" + tableName + "WHERE " + LINE +" = " + key).toString();
		ResultSet result = null;
		try {
			result = sqlUtil.executeQuery(query.toString());
			
			return result.getNString("Line");
			
		} catch (SQLException e) {
			e.printStackTrace();
		}
		

		return null;
	}

	@Override
	public void update(Integer key, String data) {
		String query = new StringBuilder("UPDATE " + tableName + "SET Text = /'" + data + " /' WHERE lineID").toString();
		
		try {
			sqlUtil.update(query);
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
	}

	@Override
	public void delete(Integer key) {
		String query = new StringBuilder("DELETE " + tableName + "SET Text = /'" + key + " /' WHERE lineID").toString();
		
		try {
			sqlUtil.remove(query);
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
	}



}
