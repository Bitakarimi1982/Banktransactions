
/*#pragma once
#include <iostream>
#include<sstream>
#include <vector>
#include <unordered_map>
#include <deque>
#include <future>
#include <thread>
#include <mutex>
#include <iomanip>
#include <fstream>
#include <osyncstream>
#include"Account.h"
#include"BankOperation.h"
#include"FileManager.h"



class Bank {
private:
    std::unordered_map<size_t, Account> accounts;
    std::vector<BankOperation> randomTransactions;
    std::deque<std::packaged_task<bool()>> taskDeque;
    std::mutex dequeMutex;
    // Additional data structure for sequential transactions
    std::deque<std::pair<BankOperation, bool>> sequentialResults;
    // Helper methods
    void executeTransaction(BankOperation& operation, std::osyncstream& syncout) noexcept;
    void writeTransactionResult(std::osyncstream& syncout, const BankOperation& operation, const bool success) noexcept;
    void executeSequentialTransaction(BankOperation& operation) noexcept;
    bool compareAccountStates() noexcept;
public:
    // Constructor
    Bank();

    // Destructor
    ~Bank();

    // Move operation
    Bank(Bank&& other) noexcept;
    Bank& operator=(Bank&& other) noexcept;

    // Copy operations are deleted
    Bank(const Bank& other) = delete;
    Bank& operator=(const Bank& other) = delete;

    // Transaction methods
    [[nodiscard]] const bool depositCapitalIntoAccount(const size_t accountID, const double money) noexcept;
    [[nodiscard]] const bool transferMoney(const size_t accountFrom, const size_t accountTo, const double amount) noexcept;
    [[nodiscard]] const bool withdrawMoney(const size_t accountFrom, const double amount) noexcept;
    
    // Transaction execution methods
    void executeRandomTransactionsConcurrently() noexcept;
    void executeThreadQueue() noexcept;


    // Sequential transaction execution methods 
    void executeRandomTransactionsSequentially() noexcept;
    bool compareTransactions() noexcept;
   

    // Public interface methods
    //[[nodiscard]] const std::unordered_map<size_t, Account> getAccountsFromFile() noexcept;
    //void writeTransactionsToFile(std::unordered_map<size_t, Account>& transactions) noexcept;

};
*/
#pragma once

#include "Account.h"
#include "BankOperation.h"
#include <deque>
#include <future>
#include <vector>
#include <unordered_map>
#include <thread>
#include"FileManager.h"
#include <mutex>
#include <fstream>
#include<iostream>



class Bank {
private:
    std::unordered_map<size_t, Account> accounts;
    std::vector<BankOperation> transactions;
    std::deque<std::packaged_task<void()>> taskQueue;
    std::mutex logMutex;
    std::mutex mtx;
    std::vector<Account> sequentialResults;
public:
    // Constructor
    Bank();
    ~Bank();
    // Move operations
    Bank(Bank&& other) noexcept;
    Bank& operator=(Bank&& other) noexcept;

    // Public interface methods
    [[nodiscard]] const bool depositCapitalIntoAccount(const size_t accountID, const double money) noexcept;
    [[nodiscard]] const bool transferMoney(const size_t accountFrom, const size_t accountTo, const double amount) noexcept;
    [[nodiscard]] const bool withdrawMoney(const size_t accountFrom, const double amount) noexcept;

    void executeRandomTransactionsConcurrently() noexcept;
    void executeThreadQueue() noexcept;
    void executeRandomTransactionsSequentially() noexcept;
    bool compareTransactions() noexcept;
    void performTransaction(const BankOperation& operation) noexcept;
    //void writeToLogFile(const std::string& message) noexcept;
    
};

