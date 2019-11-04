package codereview;

public interface Protocol {
	String wrap(String messege);
	String unwrap(String messege);
	boolean isValid(String messege);
}
