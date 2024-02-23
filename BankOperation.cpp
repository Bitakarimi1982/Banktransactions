#include "BankOperation.h"
#include <cstdlib>
#include<random>

// Implementation of BankOperation class
RandomBankOperation::RandomBankOperation() : gen(std::random_device{}()) {}

/*int RandomBankOperation::getRandomNumber(int min, int max) {
    return min + rand() % (max - min + 1);
}*/

[[nodiscard]] BankOperation RandomBankOperation::createRandomBankOperation() noexcept {
    RandomBankOperation randomOp;
    std::uniform_int_distribution<> typeDist(0, 2);
    TransactionType type = static_cast<TransactionType>(typeDist(randomOp.gen));
    std::uniform_int_distribution<> idDist(0, 1000);
    size_t sourceId = idDist(randomOp.gen);
    size_t destinationId = idDist(randomOp.gen);
    std::uniform_real_distribution<> amountDist(1000.0, 10000.0);
    double amount = amountDist(randomOp.gen);
    BankOperation operation{ type, sourceId, destinationId, amount };
    // Implement logic to generate random operation
    return operation;
}