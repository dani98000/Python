package il.co.ilrd.crud;

import java.io.IOException;
import java.sql.SQLException;
import javax.servlet.ServletException;
import javax.servlet.ServletInputStream;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import il.co.ilrd.mysql.CrudSQLLogMonitor;
import il.co.ilrd.networking.Validator;
/**
 * Servlet implementation class IOT
 */
@WebServlet("/crud")
public class CRUDServlet extends HttpServlet {
	private final static String DATABASE_NAME = "IOT";
	private final static String TABLE_NAME = "Evenets";
	private final static String USERNAME = "daniel";
	private final static String PASSWORD = "ct,h kvmkhj";
	private static final long serialVersionUID = 1L;
	private CrudSQLLogMonitor crud;
	
    /**
     * @throws SQLException 
     * @see HttpServlet#HttpServlet()
     */
    public CRUDServlet() throws SQLException {
        super();
        crud = new CrudSQLLogMonitor(DATABASE_NAME, TABLE_NAME,
				USERNAME, PASSWORD);
    }

	/**
	 * @see HttpServlet#doPost(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		byte[] body = new byte[request.getContentLength()];
		ServletInputStream inputStream = request.getInputStream();
		inputStream.read(body);
		crud.create(new String(Validator.unWrap(body)).trim());
		response.getOutputStream().write(body);
		response.setStatus(200);
	}
}