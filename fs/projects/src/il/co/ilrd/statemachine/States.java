package il.co.ilrd.statemachine;

public enum States {

	ERROR {
		public States checkValidity(char next) {
			return ERROR;
		}

	},
	NUM_READY {
		public States checkValidity(char next) {
			if (Character.isDigit(next)) {
				System.out.println("This is a number");

				return CHAR_READY;
			}

			return ERROR;
		}

	},
	CHAR_READY {
		public States checkValidity(char next) {
			if (Character.isLetter(next)) {
				System.out.println("This is a character");

				return NUM_READY;
			}

			return ERROR;
		}
	};

	abstract public States checkValidity(char next);
}
