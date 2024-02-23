#pragma once
#include <iostream>
#include <string>
#include <optional>
#include <unordered_map>

class Account {
private:
    std::string ownerName;
    int accountID;
    double balance;

public:
    // Constructor
    Account(const std::string& name, int ID, double initialBalance);

    // Destructor
    ~Account();

    Account(const Account& other); 

    // Zuweisungsoperator
    Account& operator=(const Account& other); 
    // Move operations
    Account(Account&& other) noexcept;
    Account& operator=(Account&& other) noexcept;


    // Overloading << operator
    friend std::ostream& operator<<(std::ostream& os, const Account& acc);

    // Getters and setters
    const std::string& getOwnerName() const;
    int getAccountID() const;
    double getBalance() const;
    void setBalance(double newBalance);

    // Public interface methods
    [[nodiscard]] const std::optional<double> withdraw(double amount) noexcept;
    void deposit(double amount) noexcept;
};


