package il.co.ilrd.mysql;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;

public class MySQLUtility implements AutoCloseable{    
	private Connection connection;
	private Statement statement;
	
	public MySQLUtility(String DBName, String username, String password) throws SQLException {
		connectToDatabase(DBName, username, password);
		statement = connection.createStatement();
	}
	
	private void connectToDatabase(String DBName, String username, String password) {
		String url = "jdbc:mysql://localhost:3306/" + DBName;
		
		try {
			connection = DriverManager.getConnection(url, username, password);
		    System.out.println("Database connected!");
		} catch (SQLException e) {
		    throw new IllegalStateException("Cannot connect the database!", e);
		}
	}
	
	public ResultSet execute(String text) throws SQLException {
		return statement.executeQuery(text);
	}
	
	public int executeModify(String text) throws SQLException {		
		return statement.executeUpdate(text);
	}
	
	public void createTable(String tableName, String parameters) throws SQLException {
		String query = "CREATE TABLE IF NOT EXISTS " + tableName + "(" + parameters + ")";
		statement.execute(query);
	}
	
	public boolean checkIfTableExists(String tableName) throws SQLException {
		java.sql.DatabaseMetaData dbm = connection.getMetaData();
		ResultSet tables = dbm.getTables(null, null, tableName, null);
		
		return tables.next();
	}
	
	@Override
	public void close() throws SQLException {
		connection.close();
		statement.close();
	}
}
