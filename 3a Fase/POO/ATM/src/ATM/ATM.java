package ATM;

/**
 *
 * @author usuario
 */
public class ATM{
	
	private boolean userAuthenticated;
	private int currentAccountNumber;
	private Screen screen;
	private Keypad keypad;
	private CashDispenser cashDispenser;
	private DepositSlot depositSlot;
	private BankDatabase bankDatabase;
	
	private static final int BALANCE_INQUIRY = 1 ;
	private static final int WITHDRAWAL = 2 ;
	private static final int DEPOSIT = 3 ;
	private static final int EXIT = 4;

	public ATM(){
		userAuthenticated = false ;
		currentAccountNumber = 0 ;
		screen = new Screen();
		keypad = new Keypad();
		cashDispenser = new CashDispenser();
		depositSlot = new DepositSlot();
		bankDatabase = new BankDatabase();
	}

	public void run(){
		while(true){
			while ( !userAuthenticated ){	
				screen.displayMessageLine("\nBem-Vindo!");
				authenticateUser();
			}
		performTransactions();
		userAuthenticated = false;
		currentAccountNumber = 0;
		screen.displayMessageLine("\nObrigado! Até Mais!");
		}
	}
	private void authenticateUser(){
		screen.displayMessage("\nPor favor,digite seu login: ");
		int accountNumber = keypad.getInput();
		screen.displayMessage("\nDigite seu PIN: ");
		int pin = keypad.getInput();
		userAuthenticated = bankDatabase.authenticateUser( accountNumber, pin );
		if ( userAuthenticated ){
				currentAccountNumber = accountNumber;
			}
		else
			screen.displayMessageLine("Login ou PIN inválidos. Tente Novamente.");
	}

	private void performTransactions(){
		Transaction currentTransaction = null;
		boolean userExited = false;
		while ( !userExited ){
			int mainMenuSelection = displayMainMenu();
			switch ( mainMenuSelection ){
				case BALANCE_INQUIRY:
				case WITHDRAWAL:
				case DEPOSIT:
					currentTransaction = createTransaction( mainMenuSelection );
					currentTransaction.execute();
					break;
				case EXIT:
					screen.displayMessageLine("\nSaindo do sistema...");
					userExited = true;
					break;
				default:
					screen.displayMessageLine("\nOpção Inválida, tente novamente.");
				break;
			}
		}
	}

	private int displayMainMenu(){
		screen.displayMessageLine("\nMenu:");
		screen.displayMessageLine("1 - Saldo");
		screen.displayMessageLine("2 - Sacar");
		screen.displayMessageLine("3 - Depositar");
		screen.displayMessageLine("4 - Sair\n");
		screen.displayMessage("Escolha uma Opção: ");
		return keypad.getInput();
	}

	private Transaction createTransaction(int type ){
		Transaction temp = null;
			switch( type ){
				case BALANCE_INQUIRY:
					temp = new BalanceInquiry(currentAccountNumber, screen, bankDatabase );
					break;
				case WITHDRAWAL:
					temp = new Withdrawal( currentAccountNumber, screen,bankDatabase, keypad, cashDispenser );		
					break;
				case DEPOSIT:
					temp = new Deposit( currentAccountNumber, screen,bankDatabase, keypad, depositSlot );
					break;
			}
			return temp;
	}
}
