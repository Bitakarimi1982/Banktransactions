
#include "Bank.h"


// Constructor
Bank::Bank() {
    // Fetch accounts from the file or generate them
    FileManager fileManager;
    accounts = fileManager.getAccountsFromFile();

    // Create random transactions
    RandomBankOperation randomBankOperation;
    for (int i = 0; i < 1000; ++i) { // Adjust the number of transactions as needed
        transactions.push_back(randomBankOperation.createRandomBankOperation());
    }
   
    
}

// Destructor
Bank::~Bank() {}

// Move operations
Bank::Bank(Bank&& other) noexcept
    : accounts(std::move(other.accounts)), transactions(std::move(other.transactions)) {}

Bank& Bank::operator=(Bank&& other) noexcept {
    if (this != &other) {
        accounts = std::move(other.accounts);
        transactions = std::move(other.transactions);
    }
    return *this;
}

// Public interface methods
const bool Bank::depositCapitalIntoAccount(const size_t accountID, const double money) noexcept {
    auto it = accounts.find(accountID);
    if (it != accounts.end()) {
        it->second.deposit(money);
        return true;
    }
    return false;
}
const bool Bank::transferMoney(const size_t accountFrom, const size_t accountTo, const double amount) noexcept {
    // Implement transfer logic

    auto itFrom = accounts.find(accountFrom);
    auto itTo = accounts.find(accountTo);
    if (itFrom != accounts.end() && itTo != accounts.end()) {
        if (itFrom->second.withdraw(amount).has_value()) {
            itTo->second.deposit(amount);
            return true;
        }
    }
    return false;
}

const bool Bank::withdrawMoney(const size_t accountFrom, const double amount) noexcept {

    auto it = accounts.find(accountFrom);
    if (it != accounts.end()) {
        return it->second.withdraw(amount).has_value();
    }
    return false;
}


void Bank::executeThreadQueue() noexcept {
    while (!taskQueue.empty()) {
        std::packaged_task<void()> task = std::move(taskQueue.front());
        taskQueue.pop_front();
        std::thread(std::move(task)).detach();
    }
}
   

void Bank::performTransaction(const BankOperation& operation) noexcept {
    static std::mutex logMutex; // Statischer Mutex, um den Zugriff auf die Protokolldatei zu synchronisieren
    std::lock_guard<std::mutex> lock(logMutex); // Sperre den Mutex, um den kritischen Abschnitt zu schützen

    std::ofstream logFile("result.csv", std::ios::app); // Öffne die Protokolldatei im Anhänge-Modus
    if (!logFile.is_open()) {
        std::cerr << "Error: Cannot open log file for writing\n";
        return;
    }

    switch (operation.type) {
    case TransactionType::DEPOSIT:
        if (depositCapitalIntoAccount(operation.destinationAccountID, operation.amount)) {
            logFile << "Deposit Successful to account:" << operation.destinationAccountID << ", money:" << operation.amount << '\n';
            
        }
        break;
    case TransactionType::WITHDRAWAL:
        if (withdrawMoney(operation.sourceAccountID, operation.amount)) {
            logFile << "Withdraw Successful from account:" << operation.sourceAccountID << ", money:" << operation.amount << '\n';
        }
        break;
    case TransactionType::TRANSFER:
        if (transferMoney(operation.sourceAccountID, operation.destinationAccountID, operation.amount)) {
            logFile << "Transfer Successful from account:" << operation.sourceAccountID << ", to Account:" << operation.destinationAccountID << ", money:" << operation.amount << '\n';

        }
        break;
    }

    logFile.close(); // Datei schließen, nachdem der Schreibvorgang abgeschlossen ist
}
void Bank::executeRandomTransactionsConcurrently() noexcept {
    for (const auto& op : transactions) {
        std::thread([&]() {
            performTransaction(op);
            }).detach();
    }
}

void Bank::executeRandomTransactionsSequentially() noexcept {
    for (const auto& op : transactions) {
        switch (op.type) {
        case TransactionType::DEPOSIT:
            depositCapitalIntoAccount(op.destinationAccountID, op.amount);
            break;
        case TransactionType::WITHDRAWAL:
            withdrawMoney(op.sourceAccountID, op.amount);
            break;
        case TransactionType::TRANSFER:
            transferMoney(op.sourceAccountID, op.destinationAccountID, op.amount);
            break;
        }
    }
}

bool Bank::compareTransactions() noexcept {
    // Debugging: Ausgabe der Konten in concurrentResultsCopy
    std::unordered_map<size_t, Account> concurrentResultsCopy;
    std::cout << "concurrentResultsCopy Konten:" << std::endl;
    for (const auto& pair : concurrentResultsCopy) {
        std::cout << "Account ID: " << pair.first << ", Balance: " << pair.second.getBalance() << std::endl;
    }

    // Debugging: Ausgabe der Konten in accounts
    std::cout << "accounts Konten:" << std::endl;
    for (const auto& pair : accounts) {
        std::cout << "Account ID: " << pair.first << ", Balance: " << pair.second.getBalance() << std::endl;
    }

    // Führe sequenzielle Transaktionen aus
    executeRandomTransactionsSequentially();

    // Debugging: Ausgabe der Konten in accounts nach sequenziellen Transaktionen
    std::cout << "accounts Konten nach sequenziellen Transaktionen:" << std::endl;
    for (const auto& pair : accounts) {
        std::cout << "Account ID: " << pair.first << ", Balance: " << pair.second.getBalance() << std::endl;
    }

    // Vergleiche die Ergebnisse
    for (const auto& pair : concurrentResultsCopy) {
        auto it = accounts.find(pair.first);
        if (it != accounts.end()) {
            if (it->second.getBalance() != pair.second.getBalance()) {
                return false; // Die Ergebnisse stimmen nicht überein
            }
        }
        else {
            return false; // Konto nicht gefunden
        }
    }

    return true; // Die Ergebnisse stimmen überein
}
