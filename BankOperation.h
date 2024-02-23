#pragma once
#include <cstdlib>
#include<random>
enum class TransactionType {
    DEPOSIT,
    WITHDRAWAL,
    TRANSFER
};

struct BankOperation {
    TransactionType type;
    size_t sourceAccountID;
    size_t destinationAccountID;
    double amount;
    //static BankOperation createRandomBankOperation() noexcept;
};


class RandomBankOperation {
private:
   // static int getRandomNumber(int min, int max);
    std::mt19937 gen;


public:
    RandomBankOperation();
    [[nodiscard]] static BankOperation createRandomBankOperation() noexcept;
   
};