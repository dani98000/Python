package il.co.ilrd.compositecalc;

public class CalcTree{
	Expresion root;
	Operation plus = (a, b) -> a + b;
	Operation minus = (a, b) -> a - b;
	Operation mult = (a, b) -> a * b;
	Operation div = (a, b) -> a / b;
	
	public CalcTree() {

		Expresion bot = new Operator(plus, new Operand(5), new Operand(9));
		Expresion bot2 = new Operator(mult,bot, new Operand(2));
		root = new Operator(plus,new Operand(3), bot2);
	}
	
	public int calculate() {
		return root.calculate();
	}
	
	public interface Expresion {
		int calculate();
	}
	
	public interface Operation {
		int operate(int nun1, int num2);
	}
	
	public class Operand implements Expresion{
		int key;
		
		public Operand(int key) {
			this.key = key;
		}
		@Override
		public int calculate() {
			return key;
		}
		
		int getKey() {
			return key;
		}
	}
	
	public class Operator implements Expresion{
		Operation operation;
		Expresion left, right;
		
		public Operator(Operation operation) {
			this.operation = operation;
		}
		
		public Operator(Operation operation, Expresion left, Expresion right) {
			this.operation = operation;
			this.right = right;
			this.left = left;
		}

		@Override
		public int calculate() {			
			return operation.operate(left.calculate(), right.calculate());
		}			
	}
}
