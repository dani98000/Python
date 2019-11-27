package il.co.ilrd.codereview;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;

public class MySQLUtility {
	private Connection connection;
	private Statement statement;
	
	public MySQLUtility(String dataBaseURL, String userName, String password) throws SQLException {
		connection = DriverManager.getConnection(dataBaseURL, userName,password);
		statement = connection.createStatement();
	}
	
	public ResultSet executeQuery(String query) throws SQLException {
		return statement.executeQuery(query);	
	}
	
	public boolean insert(String query) throws SQLException {
		return statement.execute(query);
	}
	
	public int update(String query) throws SQLException {
		return statement.executeUpdate(query);
	}
	
	public int remove(String query) throws SQLException {
		return statement.executeUpdate(query);
	}
	
	public void close() throws SQLException {
		statement.close();
		connection.close();
	}
	
	public void createTable(String tableName) throws SQLException {
		statement.execute("CREATE TABLE " + tableName + " (lineID INT PRIMARY KEY, Text TEXT)");
	}
}
