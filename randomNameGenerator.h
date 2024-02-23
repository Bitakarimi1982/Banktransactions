#pragma once
#include "Account.h"
#include<string>
#include<random>
class RandomNameGenerator
{
private:
    std::default_random_engine randomEngine;
    std::vector<std::string> namesList; // List of names
public:
    
    RandomNameGenerator();
    ~RandomNameGenerator();

    // Copy and move operations are deleted
    RandomNameGenerator(const RandomNameGenerator&) = delete;
    RandomNameGenerator& operator=(const RandomNameGenerator&) = delete;
    RandomNameGenerator(RandomNameGenerator&&) = delete;
    RandomNameGenerator& operator=(RandomNameGenerator&&) = delete;

    // Public interface methods
    [[nodiscard]] const std::string generateRandomName() noexcept;
    [[nodiscard]] const double generateRandomBalance() noexcept;
};

