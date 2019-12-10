package il.co.ilrd.crud;

import java.io.IOException;
import java.io.PrintWriter;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletContext;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.Cookie;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

/**
 * Servlet implementation class HelloWorld
 */
@WebServlet("/HelloWorld")
public class HelloWorldServlet extends HttpServlet {
	private static final long serialVersionUID = 1L;

	/**
	 * @see HttpServlet#HttpServlet()
	 */
	public HelloWorldServlet() {
		super();
		// TODO Auto-generated constructor stub
	}

	/**
	 * @see HttpServlet#doGet(HttpServletRequest request, HttpServletResponse
	 *      response)
	 */
	protected void doGet(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {
		/*
		 * response.setContentType("text/html"); PrintWriter writer =
		 * response.getWriter(); String name = (String) request.getParameter("name");
		 * Cookie cookie = new Cookie("name", name); response.addCookie(cookie);
		 * if(request.getCookies() != null) { writer.
		 * println("<h1 align=\"middle\" style=\"font-size:600%; color:pink;\">Hello " +
		 * name + " </h1>"); }else { writer.
		 * println("<h1 align=\"middle\" style=\"font-size:600%; color:red; \">Hello Visitor </h1>"
		 * ); } writer.
		 * println("<p style=\"text-align:center;\"><img src=\"https://i.ytimg.com/vi/Rz3M60VlVls/maxresdefault.jpg\"></p>"
		 * );
		 */

		ServletContext context = this.getServletContext();
		RequestDispatcher dispatcher = context.getRequestDispatcher("/Home.jsp");
		dispatcher.forward(request, response);

	}
}
