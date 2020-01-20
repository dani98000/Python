package il.co.ilrd.servlets;

import java.io.IOException;
import java.sql.SQLException;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import com.google.gson.JsonObject;
import il.co.ilrd.util.Company;
import il.co.ilrd.util.DatabaseUtil;
import il.co.ilrd.util.JsonUtil;

/**
 * Servlet implementation class Login
 */
@WebServlet("/Login")
public class Login extends HttpServlet {
	private static final long serialVersionUID = 1L;
    
	/**
	 * @see HttpServlet#HttpServlet()
	 */
	public Login() {
		super();
		// TODO Auto-generated constructor stub
	}

	/**
	 * @see HttpServlet#doGet(HttpServletRequest request, HttpServletResponse
	 *      response)
	 */
	protected void doGet(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {
		response.getWriter().append("Served at: ").append(request.getContextPath());
	}

	/**
	 * @see HttpServlet#doPost(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		byte[] body = new byte[request.getContentLength()];
		request.getInputStream().read(body);
		JsonObject json = JsonUtil.toJsonObject(new String(body));
		String email = json.get("email").getAsString();
		String password = json.get("password").getAsString();
		try {
			Company company = Company.login(email, password);
			if(company == null) {
				response.setStatus(201);
			}else {
				DatabaseUtil.getInstance().generateToken(response, company);
				response.setStatus(200);
			}
		} catch (SQLException e) {
			e.printStackTrace();
			response.setStatus(500);
		}
	}
}
