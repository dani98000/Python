package il.co.ilrd.mysql;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;

public class MySQLUtility implements AutoCloseable{    
	private Connection connection;
	private Statement statement;
	
	static {
		try {
			DriverManager.registerDriver(new com.mysql.jdbc.Driver());
		} catch (SQLException e) {
			e.printStackTrace();
		}
	}
	
	public MySQLUtility(String dbAddress, String user, String password) throws SQLException {
		String url = String.format("jdbc:mysql://%s?user=%s&password=%s",
							dbAddress, user, password);
		connect(url);
		statement = connection.createStatement();
	}
	
	public MySQLUtility(String dbAddress, String dbName, String user, String password) throws SQLException {
		String url = String.format("jdbc:mysql://%s/%s?user=%s&password=%s",
							dbAddress, dbName, user, password);
		connect(url);
		statement = connection.createStatement();
	}
	
	public MySQLUtility(String dbAddress, String dbName, String user, String password, boolean exists) throws SQLException {
		if(!exists) {
			MySQLUtility sqlUtil = new MySQLUtility(dbAddress, user, password);
			sqlUtil.createDB(dbName);
		}
		String url = String.format("jdbc:mysql://%s/%s?user=%s&password=%s",
							dbAddress, dbName, user, password);
		System.out.println("url: " + url);
		connect(url);
		statement = connection.createStatement();
	}
	
	private void connect(String url) {
		try {
			connection = DriverManager.getConnection(url);
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
	
	public void createTable(String tableName, String parameters) {
		String query = "CREATE TABLE IF NOT EXISTS " + tableName + parameters;
		try {
			System.out.println("Res: " + statement.execute(query));
		} catch (SQLException e) {
			e.printStackTrace();
		}
		System.out.println(query);
	}
	
	public boolean databaseExists(String dbName) throws SQLException {
		ResultSet resultSet = connection.getMetaData().getCatalogs();

		//iterate each catalog in the ResultSet
		while (resultSet.next()) {
		  if(dbName.equals(resultSet.getString(1))){
			  return true;
		  }
		}
		resultSet.close();
		
		return false;
	}
	
	public void createDB(String dbName) throws SQLException {
		statement.execute("CREATE DATABASE IF NOT EXISTS " + dbName);
	}
	
	public void deleteDB(String dbName) throws SQLException {
		
		statement.execute("DROP DATABASE " + dbName);
	}

	public void useDB(String dbName) throws SQLException {
		statement.execute("USE " + dbName);
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
