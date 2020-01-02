package il.co.ilrd.util;

import java.sql.SQLException;

import com.google.gson.Gson;
import com.google.gson.JsonObject;

public class Product {
	private final String companyName;
	private final String productName;
	private final String category;
	private final String catalogNumber;
	private final String description;
	
	public Product(String catalogNumber, String productName, String description, String companyName, String category) {
		this.catalogNumber = catalogNumber;
		this.productName = productName;
		this.description = description;
		this.companyName = companyName;
		this.category = category;
	}
	
	public Product(String json, String companyName) {
		if (null == json) {
			throw new IllegalArgumentException();
		}
		
		JsonObject productJson = JsonUtil.toJsonObject(json);
		
		this.catalogNumber = productJson.get("catNumber").getAsString();
		this.productName = productJson.get("prodName").getAsString();
		this.description = productJson.get("desc").getAsString();
		this.category = productJson.get("catName").getAsString();
		this.companyName = companyName;
	}
	
	public void save() throws SQLException {
		DatabaseUtil.getInstance().saveProduct(this);
	}
	
	public void update() throws SQLException {
		DatabaseUtil.getInstance().updateProduct(this);
	}
	
	public void delete() throws SQLException {
		DatabaseUtil.getInstance().deleteProduct(this);
	}
	
	public String toJson() {
		Gson gson = new Gson();
		
		return gson.toJson(this);
	}
	
	public String getCatalogNumber() {
		return catalogNumber;
	}
	
	public String getCategory() {
		return category;
	}

	public String getProductName() {
		return productName;
	}

	public String getDescription() {
		return description;
	}

	public String getCompanyName() {
		return companyName;
	}
}

