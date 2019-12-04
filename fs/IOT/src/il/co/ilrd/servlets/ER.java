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
 * Servlet implementation class ER
 */
@WebServlet("/ER")
public class ER extends HttpServlet {
	private static final long serialVersionUID = 1L;
	private static String dbAddress = "localhost:3306";
	private static String username = "daniel";
	private static String password = "ct,h kvmkhj";
	
    /**
     * @see HttpServlet#HttpServlet()
     */
    public ER() {
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
		String email = json.get("email").getAsString();
		String name = json.get("name").getAsString();
		String deviceSN = json.get("deviceSN").getAsString();
		String productNumber = json.get("productNumber").getAsString();

		try {
			MySQLUtility sqlUtil = new MySQLUtility(dbAddress, companyName, username, password, true);
			int numRowsEffected = insertIntoTable(sqlUtil, email, name, deviceSN, productNumber);
			if(numRowsEffected != 1) {
				throw new SQLException("Coudn't insert product to table");
			}
		} catch (SQLException e) {
			e.printStackTrace();
			response.setStatus(500);
			response.getWriter().append("Database Error!");
			
			return;
		}

		response.getWriter().append("Product added successfuly!");
		response.setStatus(200);
	}
	
	private int insertIntoTable(MySQLUtility sqlUtil, 
								String email, String name, String deviceSN, String productNumber) throws SQLException {
		String query = String.format("INSERT INTO Clients (email, name, deviceSN, productNumber) "
				 		   + "VALUES('%s','%s','%s','%s')", email, name, deviceSN, productNumber);
		
		return sqlUtil.executeModify(query);	
	}
}
