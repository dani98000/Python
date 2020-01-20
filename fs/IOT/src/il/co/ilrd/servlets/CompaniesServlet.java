package il.co.ilrd.servlets;

import java.io.IOException;
import java.sql.SQLException;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import com.google.gson.JsonObject;

import il.co.ilrd.gateway.JsonUtil;
import il.co.ilrd.mysql.MySQLUtility;

/**
 * Servlet implementation class CR
 */
@WebServlet("/companies")
public class CompaniesServlet extends HttpServlet {
	private static final long serialVersionUID = 1L;
	private static String dbAddress = "localhost:3306";
	private static String username = "daniel";
	private static String password = "ct,h kvmkhj";
	
    /**
     * @see HttpServlet#HttpServlet()
     */
    public CompaniesServlet() {
        super();
        // TODO Auto-generated constructor stub
    }

	/**
	 * @see HttpServlet#doGet(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		// TODO Auto-generated method stub
		response.getWriter().append("Unsupported Opperation: ").append("Please use POST");
	}

	/**
	 * @see HttpServlet#doPost(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		byte[] body = new byte[request.getContentLength()];
		request.getInputStream().read(body);
		JsonObject json = JsonUtil.toJsonObject(new String(body));
		String companyName = json.get("companyName").getAsString();
		if(companyName == null) {
			throw new IllegalArgumentException();
		}
		try {
			MySQLUtility sqlUtil = createDatabase(companyName);
			createClientsTable(sqlUtil);
		} catch (SQLException e) {
			response.setStatus(500);
			response.getWriter().append("Database Error!");
			
			return;
		}
		response.getWriter().append("Company added successfuly!");
		response.setStatus(200);
	}
	
	private MySQLUtility createDatabase(String companyName) throws SQLException {
		MySQLUtility sqlUtil = new MySQLUtility(dbAddress, username, password);
		if(sqlUtil.databaseExists(companyName)) {
			throw new SQLException("Database " + companyName + " Already exists!!");
		}else {
			return new MySQLUtility(dbAddress, companyName, username, password, false);
		}
	}
	
	public void createClientsTable(MySQLUtility sqlUtil) {
		sqlUtil.createTable("Clients", "(email VARCHAR(320) NOT NULL,"
									  + "name VARCHAR(50) NOT NULL," 
									  + "productNumber VARCHAR(50) NOT NULL,"
									  + "deviceSN VARCHAR(50) NOT NULL PRIMARY KEY" + ")");
	}
}