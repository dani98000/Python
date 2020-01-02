package il.co.ilrd.util;

import java.io.IOException;
import java.sql.SQLException;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.springframework.security.crypto.bcrypt.BCryptPasswordEncoder;

import com.google.gson.JsonObject;

public class Company {
	private static final BCryptPasswordEncoder ENCODER = new BCryptPasswordEncoder();
	
	private final String email;
	private final String companyName;
	private final String password;
	
	public Company(String email, String companyName, String password) {
		this.companyName = companyName;
		this.email = email;
		this.password = ENCODER.encode(password);
	}
	
	public Company(String json) {
		if (null == json) {
			throw new IllegalArgumentException();
		}
		
		JsonObject userJson = JsonUtil.toJsonObject(json);
		
		this.email = userJson.get("email").getAsString();
		this.companyName = userJson.get("companyName").getAsString();
		this.password = ENCODER.encode(userJson.get("password").getAsString());
	}
	
	public void save() throws SQLException {
		DatabaseUtil.getInstance().saveCompany(this);
	}
	
	public void delete() throws SQLException {
		DatabaseUtil.getInstance().deleteCompany(this);
	}
	
	public static void logout(HttpServletRequest request, HttpServletResponse response) throws SQLException, IOException {
		DatabaseUtil.getInstance().invalidateToken(request, response);
	}
	
	public static Company login(final String email, String password) throws SQLException {		
		return DatabaseUtil.getInstance().login(email, password, ENCODER);
	}

	
	public String getCompanyName() {
		return companyName;
	}

	public String getEmail() {
		return email;
	}

	public String getPassword() {
		return password;
	}
}
