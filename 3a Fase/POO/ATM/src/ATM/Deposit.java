package ATM;


import ATM.Screen;

public class Deposit extends Transaction{
	private double amount;
	private Keypad keypad; 
	private DepositSlot depositSlot;
	private final static int CANCELED = 0 ;

	public Deposit(int userAccountNumber, Screen atmScreen,BankDatabase atmBankDatabase, 
		Keypad atmKeypad,DepositSlot atmDepositSlot )
	{
		super( userAccountNumber, atmScreen, atmBankDatabase );
		keypad = atmKeypad;
		depositSlot = atmDepositSlot;
	}

        @Override
	public void execute(){
		BankDatabase bankDatabase = getBankDatabase();
		Screen screen = getScreen();
		amount = promptForDepositAmount();
		if (amount != CANCELED){
			screen.displayMessage("\nPor favor,insira o Envelope ");
			screen.displayDollarAmount( amount );
			screen.displayMessageLine(".");
			boolean envelopeReceived = depositSlot.isEnvelopeReceived();
			if( envelopeReceived ){
				screen.displayMessageLine("\nSeu envelope foi " + 
					"rercebido.\nNOTA: O dinheiro não estará  "
					+ "disponível até checarmos o envelope,bem como "
					+ "sua conta.");
				bankDatabase.credit( getAccountNumber(), amount );
			}else{
				screen.displayMessageLine("\nVocê não inseriu um "
					+ "envelope, então cancelamos sua transação.");
			}
		}else{
			screen.displayMessageLine("\nCancelando transação...");
		}
	}

	private double promptForDepositAmount(){
		Screen screen = getScreen();
		screen.displayMessage("\nPor favor,insira o valor em  " +
			"CENTAVOS (ou 0 para cancelar): ");
		int input = keypad.getInput();
		if ( input == CANCELED) 
			return CANCELED ;
		else{
			return (double) input / 100;
		}
	}
}