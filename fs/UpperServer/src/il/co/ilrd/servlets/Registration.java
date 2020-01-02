package il.co.ilrd.servlets;

import java.io.IOException;
import java.net.URI;
import java.net.http.HttpClient;
import java.net.http.HttpRequest;
import java.net.http.HttpRequest.BodyPublishers;
import java.net.http.HttpResponse;
import java.net.http.HttpResponse.BodyHandlers;
import java.sql.SQLException;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import com.google.gson.Gson;
import com.google.gson.JsonObject;

import il.co.ilrd.util.Company;
import il.co.ilrd.util.DatabaseUtil;

/**
 * Servlet implementation class Registeration
 */
@WebServlet("/Registration")
public class Registration extends HttpServlet {
	private static final long serialVersionUID = 1L;
    
	/**
	 * @see HttpServlet#HttpServlet()
	 */
	public Registration() {
		super();
		// TODO Auto-generated constructor stub
	}

	/**
	 * @see HttpServlet#doGet(HttpServletRequest request, HttpServletResponse
	 *      response)
	 */
	protected void doGet(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {
		DatabaseUtil dbUtil = null;
		try {
			dbUtil = DatabaseUtil.getInstance();
		} catch (SQLException e) {
			e.printStackTrace();
		}
		boolean tokenFound = dbUtil.validateToken(request);
		if (tokenFound) {
			response.sendRedirect("http://localhost:8081/Products");
			return;
		}
		RequestDispatcher rd = request.getRequestDispatcher("html/home.html");
		rd.forward(request, response);
	}

	/**
	 * @see HttpServlet#doPost(HttpServletRequest request, HttpServletResponse
	 *      response)
	 */
	protected void doPost(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {
		byte[] body = new byte[request.getContentLength()];
		request.getInputStream().read(body);
		int resStatus = 0;
		
		try {
			DatabaseUtil dbUtil = DatabaseUtil.getInstance();
			Company company = new Company(new String(body));
			company.save();
			String json = prepareCRJson(company);
			int status = sendPost(json);
			if(status == 200) {
				dbUtil.generateToken(response, company);
			} else {
				try {
					company.delete();
				} catch (SQLException e) {
					e.printStackTrace();
					resStatus = 500;
				}
				resStatus = 403;
			}
		} catch (SQLException | InterruptedException e) {
			e.printStackTrace();
			resStatus = 500;
		}
		
		response.setStatus(resStatus);
	}
	
	private int sendPost(String json) throws IOException, InterruptedException {
		HttpClient client = HttpClient.newHttpClient();
		
		HttpRequest req = HttpRequest.newBuilder()
				.uri(URI.create("http://localhost:5555" ))
				.header("Content-Type", "application/json")
				.POST(BodyPublishers.ofString(json))
				.build();
		
		
		HttpResponse<String> response = client.send(req, BodyHandlers.ofString());
		
		return response.statusCode();
	}
	
	private String prepareCRJson(Company company) {
		Gson gson = new Gson();
		JsonObject data = new JsonObject();
		JsonObject json = new JsonObject();
		data.addProperty("companyName", company.getCompanyName());
		json.addProperty("commandType", "CR");
		json.addProperty("data", data.toString());
		
		return gson.toJson(json);
	}
}