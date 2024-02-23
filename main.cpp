#include<iostream>
#include"Bank.h"
int main() {
    // Create a bank and execute random transactions concurrently
    Bank bank;
    bank.executeRandomTransactionsConcurrently();
    if (bank.compareTransactions()) {
        std::cout << "Transaction results match!" << std::endl;
    }
    else {
        std::cerr << "Error: Transaction results do not match." << std::endl;
    }
    
    return 0;
}