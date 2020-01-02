package il.co.ilrd.util;

import java.io.IOException;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.time.Period;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.springframework.security.crypto.password.PasswordEncoder;

import il.co.ilrd.mysql.MySQLUtility;

public class DatabaseUtil {
	private static String dbAddress = "localhost:3306";
	private static String dbUsername = "daniel";
	private static String dbPassword = "ct,h kvmkhj";
	private static final String jwtTokenCookieName = "JWT-TOKEN";
	private static final String signingKey = "signingKey4LIFDSAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAE";

	private static final String COMPANIES_TABLE = "Companies";
	private static final String PRODUCTS_TABLE = "Products";

	private final MySQLUtility sqlUtil;
	private static volatile DatabaseUtil instance;

	private PreparedStatement insertCompany;
	private PreparedStatement searchCompanyByEmail;
	private PreparedStatement insertProduct;
	private PreparedStatement updateProduct;
	private PreparedStatement deleteProduct;
	private PreparedStatement deleteCompany;

	public static DatabaseUtil getInstance() throws SQLException {
		if (instance == null) {
			synchronized (DatabaseUtil.class) {
				if (instance == null) {
					instance = new DatabaseUtil();
				}
			}
		}

		return instance;
	}

	private DatabaseUtil() throws SQLException {
		sqlUtil = new MySQLUtility(dbAddress, "IOT", dbUsername, dbPassword);
		init();
	}

	private void init() throws SQLException {
		insertCompany = sqlUtil.prepareStatement("INSERT INTO " + COMPANIES_TABLE + " VALUES(?, ?, ?)");
		insertProduct = sqlUtil.prepareStatement("INSERT INTO " + PRODUCTS_TABLE + " VALUES (?, ?, ?, ?, ?, ?)");
		searchCompanyByEmail = sqlUtil.prepareStatement("SELECT * FROM " + COMPANIES_TABLE + " WHERE email = ?");
		deleteProduct = sqlUtil.prepareStatement("DELETE FROM " + PRODUCTS_TABLE + " Where companyName = ? AND catalogNumber = ?");
		deleteCompany = sqlUtil.prepareStatement("DELETE FROM " + COMPANIES_TABLE + " Where companyName = ?");
		updateProduct = sqlUtil.prepareStatement("UPDATE " + PRODUCTS_TABLE + " SET productName = ?, category = ?," +
											     "description = ? WHERE catalogNumber = ? AND companyName = ?");
	}

	public Company login(String email, String password, PasswordEncoder encoder) throws SQLException {
		searchCompanyByEmail.setString(1, email);

		ResultSet rs = searchCompanyByEmail.executeQuery();

		if (!rs.next()) {
			return null;
		}
		
		String hashedPassword = rs.getString("password");
		if(encoder.matches(password, hashedPassword)) {
			return new Company(rs.getString("email"),
							   rs.getString("companyName"),
							   password
							  );
		}

		return null;
	}

	public void saveCompany(Company company) throws SQLException {
		insertCompany.setString(1, company.getEmail());
		insertCompany.setString(2, company.getCompanyName());
		insertCompany.setString(3, company.getPassword());

		insertCompany.execute();
	}

	public void saveProduct(Product product) throws SQLException {
		insertProduct.setString(1, product.getCompanyName());
		insertProduct.setString(2, product.getProductName());
		insertProduct.setString(3, product.getCategory());
		insertProduct.setString(4, product.getCatalogNumber());
		insertProduct.setString(5, product.getDescription());
		insertProduct.setString(6, null);

		insertProduct.execute();
	}
	
	public void updateProduct(Product product) throws SQLException {
		updateProduct.setString(1, product.getProductName());
		updateProduct.setString(2, product.getCategory());
		updateProduct.setString(3, product.getDescription());
		updateProduct.setString(4, product.getCatalogNumber());
		updateProduct.setString(5, product.getCompanyName());
		
		updateProduct.execute();
	}
	
	public void deleteProduct(Product product) throws SQLException {
		deleteProduct.setString(1, product.getCompanyName());
		deleteProduct.setString(2, product.getCatalogNumber());
		
		deleteProduct.execute();
	}
	
	public void deleteCompany(Company company) throws SQLException {
		deleteCompany.setString(1, company.getCompanyName());
		
		deleteCompany.execute();
	}

	public boolean validateToken(String token) throws IOException {
		return JwtUtil.validateToken(token, signingKey);
	}

	public boolean validateToken(HttpServletRequest request) throws IOException {
		String token = CookieUtil.getValue(request, jwtTokenCookieName);
		
		return JwtUtil.validateToken(token, signingKey);
	}
	
	public String extractCompanyName(HttpServletRequest request) {
		return JwtUtil.parseToken(request, jwtTokenCookieName, signingKey);
	}
	
	public void invalidateToken(String token) throws IOException {
		JwtUtil.invalidateRelatedTokens(token);
	}
	
	public void invalidateToken(HttpServletRequest request, HttpServletResponse response) {
		request.setAttribute("companyName", JwtUtil.parseToken(request, jwtTokenCookieName, signingKey));
        JwtUtil.invalidateRelatedTokens(request);
        CookieUtil.clear(response, jwtTokenCookieName);	
	}

	public String generateToken(HttpServletResponse response, Company company) {
		String token = JwtUtil.generateToken(signingKey, company.getCompanyName());
		CookieUtil.create(response, jwtTokenCookieName, token, false, Period.ofDays(30), "localhost");
		
		return token;
	}
}
