package Transactions;

import main.*;
import ATM.*;

public class Transaction{
    private int accountNumber;
    
    public Transaction(int x){
        this.accountNumber = x;
    }
    
    public int getAccountNumber(){
    return accountNumber; 
    }
    
    /**
     *
     * @return
     */
    public static int execute(){
        int menuOption = 0;
        while (menuOption != 4)
        { 
            menuOption=menu();
            switch (menuOption)
            {
            case 1:
                BalanceInquiry.execute();
                break;
            case 2:
                System.out.print("\nPor Favor,digite o valor do depósito: $ ");
                depositAmt = kbd.nextDouble();
                a.balance=deposit(depositAmt, currentBal);
                break;
            case 3:
                System.out.print("\nEnter Amount You Wish to Withdrawl: $ ");
                withdrawAmt = kbd.nextDouble();

                while(withdrawAmt>currentBal){
                    System.out.print("ERROR: INSUFFICIENT FUNDS!! "
                            + "PLEASE ENTER A DIFFERENT AMOUNT: $");
                    withdrawAmt = kbd.nextDouble();
                }

                currentBal = withdraw(currentBal, withdrawAmt);
                break;
            case 4:
                System.out.print("\nThank For Using My ATM.  Have a Nice Day.  Good-Bye!");
                System.exit(0);
                break;
            }
        }
    }

public static int menu()
    {
        int menuChoice;
        do
        { 
            System.out.print("\nMain Menu:"
                    + "\n 1. Saldo \n 2. Depositar"
                    + "\n 3. Sacar\n 4. Sair\n\n");

            menuChoice = kbd.nextInt();

            if (menuChoice < 1 || menuChoice > 4){
                System.out.println("Opção Inválida");
            }

        }while (menuChoice < 1 || menuChoice > 4);

        return menuChoice;
    }



}