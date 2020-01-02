package il.co.ilrd.servlets;

import java.io.IOException;
import java.net.URI;
import java.net.http.HttpClient;
import java.net.http.HttpRequest;
import java.net.http.HttpResponse;
import java.net.http.HttpRequest.BodyPublishers;
import java.net.http.HttpResponse.BodyHandlers;
import java.sql.SQLException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import com.google.gson.Gson;
import com.google.gson.JsonObject;

import il.co.ilrd.util.Company;
import il.co.ilrd.util.DatabaseUtil;
import il.co.ilrd.util.JsonUtil;
import il.co.ilrd.util.Product;

/**
 * Servlet implementation class products
 */
@WebServlet("/Products")
public class Products extends HttpServlet {
	private static final long serialVersionUID = 1L;

	/**
	 * @see HttpServlet#HttpServlet()
	 */

	@Override
	public void service(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		if (request.getMethod().equalsIgnoreCase("PATCH")) {
			doPatch(request, response);
		} else {
			super.service(request, response);
		}
	}

	public Products() {
		super();
	}

	/**
	 * @see HttpServlet#doGet(HttpServletRequest request, HttpServletResponse
	 *      response)
	 */
	protected void doGet(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {
		try {
			String companyName = DatabaseUtil.getInstance().extractCompanyName(request);
			if (companyName == null) {
				response.sendRedirect("/html/home.html");
				
				return;
			}
			request.setAttribute("companyName", companyName);
			request.getRequestDispatcher("/html/products.jsp").forward(request, response);
		} catch (SQLException e) {
			e.printStackTrace();
		}
	}

	/**
	 * @see HttpServlet#doPost(HttpServletRequest request, HttpServletResponse
	 *      response)
	 */
	protected void doPost(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {
		byte[] body = new byte[request.getContentLength()];
		request.getInputStream().read(body);

		try {
			DatabaseUtil dbUtil = DatabaseUtil.getInstance();
			boolean tokenFound = dbUtil.validateToken(request);
			if (!tokenFound) {
				response.setStatus(401);
				response.getWriter().close();
				return;
			}

			Product product = new Product(new String(body), dbUtil.extractCompanyName(request));
			product.save();
			String json = preparePRJson(product);
			
			int status = sendPost(json);
			if(status == 200) {
				response.setStatus(201);				
			}else {
				product.delete();
				response.setStatus(403);				
			}
		} catch (SQLException | InterruptedException e1) {
			e1.printStackTrace();
			response.setStatus(500);
		}
	}

	protected void doPatch(HttpServletRequest request, HttpServletResponse response) throws IOException {
		byte[] body = new byte[request.getContentLength()];
		request.getInputStream().read(body);
		JsonObject json = JsonUtil.toJsonObject(new String(body));
		try {
			DatabaseUtil dbUtil = DatabaseUtil.getInstance();
			boolean tokenFound = dbUtil.validateToken(request);
			if (!tokenFound) {
				response.setStatus(401);
				response.getWriter().close();
				return;
			}

			Product product = new Product(json.get("catNumber").getAsString(), json.get("prodName").getAsString(),
										  json.get("desc").getAsString(), dbUtil.extractCompanyName(request),
										  json.get("catName").getAsString());
			
			product.update();
			response.setStatus(200);
		} catch (SQLException e) {
			e.printStackTrace();
			response.setStatus(500);
		}
	}

	protected void doDelete(HttpServletRequest request, HttpServletResponse response) throws IOException {
		byte[] body = new byte[request.getContentLength()];
		request.getInputStream().read(body);
		JsonObject json = JsonUtil.toJsonObject(new String(body));
		try {
			DatabaseUtil dbUtil = DatabaseUtil.getInstance();
			boolean tokenFound = dbUtil.validateToken(request);
			if (!tokenFound) {
				response.setStatus(401);
				response.getWriter().close();
				return;
			}

			String companyName = dbUtil.extractCompanyName(request);
			Product product = new Product(json.get("catNumber").getAsString(), null, null, companyName, null);
			
			product.delete();
			response.setStatus(200);
		} catch (SQLException e) {
			e.printStackTrace();
			response.setStatus(500);
		}
	}
	
	private String preparePRJson(Product product) {
		Gson gson = new Gson();
		JsonObject data = new JsonObject();
		JsonObject json = new JsonObject();
		data.addProperty("companyName", product.getCompanyName());
		data.addProperty("catalogNumber", product.getCatalogNumber());
		json.addProperty("commandType", "PR");
		json.addProperty("data", data.toString());
		
		return gson.toJson(json);
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
}