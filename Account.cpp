#include "Account.h"


// Implementation of Account class

Account::Account(const std::string& name, int ID, double initialBalance)
    : ownerName(name), accountID(ID), balance(initialBalance) {}

Account::~Account() {}

Account::Account(const Account& other): 
    accountID(other.accountID),
    ownerName(other.ownerName), 
    balance(other.balance) {}
Account& Account::operator=(const Account& other) {
    if (this != &other) { // Selbstzuweisung vermeiden
        accountID = other.accountID;
        ownerName = other.ownerName;
        balance = other.balance;
    }
    return *this;
}
Account::Account(Account&& other) noexcept
    : ownerName(std::move(other.ownerName)),
    accountID(other.accountID),
    balance(other.balance) {
    other.accountID = -1; // Mark the moved-from object
}


Account& Account::operator=(Account&& other) noexcept {
    if (this != &other) {
        ownerName = std::move(other.ownerName);
        accountID = other.accountID;
        balance = other.balance;
        other.accountID = -1; // Mark the moved-from object
    }
    return *this;
}

const std::string& Account::getOwnerName() const {
    return ownerName;
}

int Account::getAccountID() const {
    return accountID;
}

double Account::getBalance() const {
    return balance;
}

void Account::setBalance(double newBalance) {
    balance = newBalance;
}

const std::optional<double> Account::withdraw(double amount) noexcept {
    if (amount > balance) {
        return std::nullopt; // Not enough funds
    }
    balance -= amount;
    return amount;
}

void Account::deposit(double amount) noexcept {
    balance += amount;
}

std::ostream& operator<<(std::ostream& os, const Account& acc) {
    os << "Account ID: " << acc.accountID << ", Owner: " << acc.ownerName << ", Balance: " << acc.balance;
    return os;
}
