package il.co.ilrd.vendingmachineV2;

public enum States {
		INIT {
			@Override
			protected void start(VendingMachineController vm) {
				vm.getMonitor().print("< Welcome to the best Vending Machine in the whole entire WORLD! >");
				vm.getMonitor().print("\t   < May i offer you something tasty? >");
				vm.displayProducts();
				System.out.println("===================================================================");

				vm.setState(WAITING_MONEY);
			}

			@Override
			protected void chooseProduct(String product, VendingMachineController vm) {
				vm.getMonitor().print("Please press |START| before doing any operation.");
				vm.setState(INIT);
			}

			@Override
			protected void insertMoney(int money, VendingMachineController vm) {
				vm.returnChange();
				vm.getMonitor().print("Please press |START| before doing any operation.");
				vm.setState(INIT);
			}

		},
		WAITING_MONEY {
			@Override
			protected void chooseProduct(String product, VendingMachineController vm) {
				vm.getMonitor().print("Please insert money before choosing a product.");
				vm.setState(WAITING_MONEY);
			}

			@Override
			protected void insertMoney(int money, VendingMachineController vm) {
				vm.setBalance(vm.getBalance() + money);
				vm.setTimer(5);
				vm.setState(WAITING_CHOICE);
			}

		},
		WAITING_CHOICE {
			@Override
			protected void checkTimeOut(VendingMachineController vm) {
				if (vm.getTimer() <= 0) {
					vm.getMonitor().print("Timeout!");
					vm.returnChange();
					vm.setState(WAITING_MONEY);
				}else
				{
					vm.setTimer(vm.getTimer() - 1);
				}
			}
			
			@Override
			protected void chooseProduct(String product, VendingMachineController vm) {
				vm.setTimer(0);
				
				// key exists
				if (vm.getProducts().containsKey(product.hashCode())) {
					Product currpProduct = vm.getProducts().get(product.hashCode());

					if (currpProduct.getPrice() <= vm.getBalance()) {
						vm.getMonitor().print("Congratz you got yourself a " + product);
						vm.returnChange();
					} else {
						vm.getMonitor().print("Not Enough Money, Dropping change.");
						vm.returnChange();
					}
				} else {
					// key does not exists
					vm.getMonitor().print("Sorry there is no such product");
				}
				vm.getMonitor().print("\t   < Thank you for buying, GoodBye =] >");
				vm.getMonitor().print("===================================================================\n");

				vm.setState(WAITING_MONEY);
			}

			@Override
			protected void insertMoney(int money, VendingMachineController vm) {
				vm.setBalance(vm.getBalance() + money);
				vm.setState(WAITING_CHOICE);
			}
		};
	
		protected void stop(VendingMachineController vm) {
			vm.getMonitor().print("\t\t\tGoodBye =]");
			vm.getMonitor().print("===================================================================\n");
			vm.setTimer(0);
			vm.setBalance(0);
			vm.setState(INIT);
		}
		
		protected void checkTimeOut(VendingMachineController vm) {
			//Do absolutely nothing.
		}
	
		protected void start(VendingMachineController vm) {
			//Do absolutely nothing.
		}
		
		protected abstract void insertMoney(int money, VendingMachineController vm);
		protected abstract void chooseProduct(String product, VendingMachineController vm);
}
