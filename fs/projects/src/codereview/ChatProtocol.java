package codereview;

public class ChatProtocol implements Protocol{
	@Override
	public String wrap(String messege) {
		return("#@" + messege + "#@");
	}

	@Override
	public String unwrap(String messege) {
		return messege.substring(2, messege.length() - 2);	
	}

	@Override
	public boolean isValid(String messege) {
		int length = messege.length();
		
		if(length < 4 || messege.charAt(0) != '#' || messege.charAt(1) != '@' 
				|| messege.charAt(length - 2) != '#' || messege.charAt(length - 1) != '@') {
					return false;			
		}
		
		return true;
	}
}
