#pragma once
#include"randomNameGenerator.h"
#include"BankOperation.h"
#include <fstream>
#include <sstream>
#include"Account.h"
#include <unordered_map>
using namespace std;
class FileManager {
private:
    std::string filename;

public:
    // Constructor
    FileManager();
    //FileManager(std::string_view);

    // Destructor
    ~FileManager();

    // Copy and move operations
    FileManager(const FileManager& other);
    FileManager& operator=(const FileManager& other);
    FileManager(FileManager&& other) noexcept;
    FileManager& operator=(FileManager&& other) noexcept;

    
    // Read accounts from the CSV file into an unordered_map
    [[noexcept]] std::unordered_map<size_t, Account> getAccountsFromFile() noexcept;

    // Write transactions to a new CSV file
    void writeTransactionsToFile(const std::vector<BankOperation>& transactions) noexcept;

    
};



