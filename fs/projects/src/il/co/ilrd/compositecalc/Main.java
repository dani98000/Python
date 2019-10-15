package il.co.ilrd.compositecalc;

public class Main {
	public static void main(String[] args) {
		CalcTree tree = new CalcTree();
		int sum = tree.calculate();
		System.out.println(sum);
	}
}
