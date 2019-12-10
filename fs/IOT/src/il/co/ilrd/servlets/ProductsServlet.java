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
 * Servlet implementation class PR
 */
@WebServlet("/products")
public class ProductsServlet extends HttpServlet {
	private static final long serialVersionUID = 1L;
	private static String dbAddress = "localhost:3306";
	private static String username = "daniel";
	private static String password = "ct,h kvmkhj";
	
    /**
     * @see HttpServlet#HttpServlet()
     */
    public ProductsServlet() {
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
		String deviceSN = json.get("deviceSN").getAsString();
		String companyName = json.get("companyName").getAsString();
		try {
			MySQLUtility sqlUtil = new MySQLUtility(dbAddress, companyName, username, password);
			sqlUtil.executeModify("INSERT INTO Products VALUES(\"" + deviceSN + "\")"); 
		} catch (SQLException e) {
			response.setStatus(500);
			response.getWriter().append("Database Error!");
			
			return;
		}

		response.getWriter().append("Product added successfuly!");
		response.setStatus(200);
	}
}
