package il.co.ilrd.vendingmachine;

public enum States implements State{
	
	INIT{
		public States chooseDrink() {
			return INIT;
		}
		public States insertMoney(int money) {
			return INIT;
		}

		
	}, WAITING_MONEY{
		public States chooseDrink() {
			return WAITING_MONEY;
		}
		public States insertMoney(int money) {
			return WAITING_CHOICE;
		}

		
	}, WAITING_CHOICE{
		public States chooseDrink() {
			return INIT;
		}
		public States insertMoney(int money) {
			return WAITING_CHOICE;
		}
	};
	
	public States stop() {
		return INIT;
	}
	
	public States start() {
		return WAITING_MONEY;
	}
}
