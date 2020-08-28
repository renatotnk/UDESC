
package Transactions;

import ATM.*;

/**
 *
 * @author UDESC
 */
public class Withdrawal extends Transaction {
   private double amount; 
    public Withdrawal(double x){
        this.amount = amount;
    }
    
   /**
     * @param x
     * @param amount
     * @return balance
    * @Override
    */
   public void execute(Account x,double amount,Money y){
       double old_balance = x.getBalance();
       if(x.getBalance() <= amount){
           System.out.printf("Quantidade não disponível em sua conta\n");
       }else if(y.getMoney() <= amount){
            System.out.printf("Quantidade selecionada não disponível neste ATM, por favor, cheque mais tarde\n");
       }else{
            x.setBalance()
       }
    }
}
