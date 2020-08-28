package ATM;

public class Withdrawal extends Transaction{
	private int amount; 
	private Keypad keypad;
	private CashDispenser cashDispenser;
	private final static int CANCELED = 6 ;

	public Withdrawal(int userAccountNumber, Screen atmScreen,BankDatabase atmBankDatabase,
	 Keypad atmKeypad,CashDispenser atmCashDispenser )
	{
		super( userAccountNumber, atmScreen, atmBankDatabase );
		keypad = atmKeypad;
		cashDispenser = atmCashDispenser;
	}

    /**
     *
     */
    @Override
	public void execute(){
		boolean cashDispensed = false;
		double availableBalance;
		BankDatabase bankDatabase = getBankDatabase();
		Screen screen = getScreen();

		do {
			amount = displayMenuOfAmounts();
			if ( amount != CANCELED){
				availableBalance = bankDatabase.getAvailableBalance( getAccountNumber());
				if( amount <= availableBalance ){
					if(cashDispenser.isSufficientCashAvailable(amount)){
						bankDatabase.debit( getAccountNumber(), amount );
						cashDispenser.dispenseCash( amount );
						cashDispensed = true; 
						screen.displayMessageLine("\nSeu dinheiro foi" + " entregue. Por favor, pegue seu dinheiro");
					
					}else
					screen.displayMessageLine("\nDinheiro Insuficiente no ATM." + "\n\nPor favor,insira uma quantidade melhor ou cheque mais tarde.");
				}else{
					screen.displayMessageLine("\nNão há dinheiro suficiente em sua conta." + "\n\nPor favor,insira uma quantidade melhor ou cheque mais tarde.");
				}
			}else{
				screen.displayMessageLine("\nCancelando transação...");
				return;
			}
		} while (!cashDispensed );
	}


	private int displayMenuOfAmounts(){
		int userChoice = 0;
		Screen screen = getScreen();
		int amounts[] = {0,20,40,60,100,200};
		while( userChoice == 0 )
		{
			screen.displayMessageLine("\nMenu de Saque:");
			screen.displayMessageLine("1 - $20");
			screen.displayMessageLine("2 - $40");
			screen.displayMessageLine("3 - $60");
			screen.displayMessageLine("4 - $100");
			screen.displayMessageLine("5 - $200");
			screen.displayMessageLine("6 - Cancelar ");
			screen.displayMessage("\nEscolha uma opção de Saque: ");
			int input = keypad.getInput();
			switch ( input ){
				case 1:
				case 2:
				case 3: 
				case 4:
				case 5: 
					userChoice = amounts[ input ];
					break;
				case CANCELED: 
					userChoice =CANCELED;
					break;
				default:
					screen.displayMessageLine("\nOpção inválida, por favor, selecione uma opção correta.");
			}
		}
		return userChoice; 
	}
}
