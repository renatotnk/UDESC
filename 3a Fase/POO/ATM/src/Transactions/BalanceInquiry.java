
package Transactions;

import ATM.*;

public class BalanceInquiry extends Transaction { 
    /**
     * @param x
     * @return x.balance 
     * @Override
     */
    public double execute(Account x){
        return x.getBalance();
    }
}
