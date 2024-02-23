#include "FileManager.h"

FileManager::FileManager() : filename("bankClients.csv") {

    // Create the file if it does not exist
    std::ofstream file(filename, std::ios::trunc);
    RandomNameGenerator nameGenerator;

    for (int i = 0; i < 1000; ++i) { // Annahme: 1000 zufällige Konten generieren
        size_t accountID = i; // Die ID wird von 0 bis 999 vergeben
        std::string ownerName = nameGenerator.generateRandomName(); // Nutzung des RandomNameGenerator
        double balance = nameGenerator.generateRandomBalance();

        file << accountID << "," << ownerName << "," << balance << "\n";
    }

    file.close();
    std::cout << "bankClients.csv file created successfully\n";
    // Create random transactions
    
}


FileManager::~FileManager() {}

FileManager::FileManager(const FileManager& other) : filename(other.filename) {}

FileManager& FileManager::operator=(const FileManager& other) {
    if (this != &other) {
        filename = other.filename;
    }
    return *this;
}

FileManager::FileManager(FileManager&& other) noexcept :
    filename(std::move(other.filename)) {}

FileManager& FileManager::operator=(FileManager&& other) noexcept {
    if (this != &other) {
        filename = std::move(other.filename);
    }
    return *this;
}

[[noexcept]] std::unordered_map<size_t, Account> FileManager::getAccountsFromFile() noexcept {

        std::unordered_map<size_t, Account> accounts;
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Error: Unable to open the file " << filename << " for reading." << std::endl;
            return accounts; // Return an empty map if the file cannot be opened
        }
        
        // Read the file line by line
        std::string line;
       
         
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            std::string token;
       
            if (!(std::getline(iss, token, ','))) {
                std::cerr << "Error: Failed to read account ID from the file." << std::endl;
                continue;
            }
            size_t accountID = std::stoi(token);
            std::string ownerName ;


            if (!(std::getline(iss, ownerName, ','))) {
                std::cerr << "Error: Failed to read owner name from the file." << std::endl;
                continue;
            }

            if (!(std::getline(iss, token))) {
                std::cerr << "Error: Failed to read balance from the file." << std::endl;
                continue;
            }
            double balance = std::stod(token);

            accounts.emplace(accountID, Account(ownerName, accountID, balance));
        }
        file.close();
       
        return accounts;
          
}

void FileManager::writeTransactionsToFile(const std::vector<BankOperation>& transactions) noexcept {
    std::ofstream file("results.csv", std::ios::trunc);

    if (!file.is_open()) {
        std::cerr << "Error: Unable to open the file results.csv for writing." << std::endl;
        return;
    }

    // Write transaction results
    for (const auto& transaction : transactions) {
        file << static_cast<int>(transaction.type) << ";"
            << transaction.sourceAccountID << ";"
            << transaction.destinationAccountID << ";"
            << transaction.amount << std::endl;

        file.close();
    }
}

   