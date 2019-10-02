package il.co.ilrd.Exam;

import java.util.HashMap;

public class Calculator {
	private HashMap<String, Operator>map = new HashMap<>();
	
	public Calculator() {
		addOperator("addition", (int a, int b)->a + b);
		addOperator("subtraction", new Operator() {
			@Override
			public int operate(int a, int b) {
				return a - b;
			}
		});
		addOperator("multiplication", new Mult());
	
		class Div implements Operator{
			@Override
			public int operate(int a, int b) {
				return a / b;
			}
		}
		
		addOperator("division", new Div());

		
	}
	
	class Mult implements Operator{
		@Override
		public int operate(int a, int b) {
			return a * b;
		}
	}
	
	private interface Operator{
		int operate(int a, int b);
	}
	
	private void addOperator(String str, Operator op) {
		map.put(str, op);
	}
	
    public int operate(String key, int a, int b) {
        return map.get(key).operate(a, b);
    }
    
    public static void main(String[] args) {
    	Calculator calc = new Calculator();
    	System.out.println(calc.operate("addition", 5, 11));
    	System.out.println(calc.operate("subtraction", 5, 11));
    	System.out.println(calc.operate("multiplication", 5, 11));
    	System.out.println(calc.operate("division", 22, 11));

    }
}
