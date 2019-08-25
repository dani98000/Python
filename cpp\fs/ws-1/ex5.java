class ex5 {
	
	public static void overflow(int x) {
		System.out.println(x);
		overflow(++x);
	}

	public static void main(String[] args) {
		
		ex5.overflow(0);
	}
}

