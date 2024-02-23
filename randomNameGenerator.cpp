#include "RandomNameGenerator.h"


RandomNameGenerator::RandomNameGenerator() {}
RandomNameGenerator::~RandomNameGenerator() {}

const std::string RandomNameGenerator::generateRandomName() noexcept {
   
    static const char alphabet[] = "abcdefghijklmnopqrstuvwxyz";
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> lenDist(5, 10);
    std::uniform_int_distribution<> charDist(0, 25);

    std::string name;
    int length = lenDist(gen);
    for (int i = 0; i < length; ++i) {
        name += alphabet[charDist(gen)];
    }

    return name;
}

const double RandomNameGenerator::generateRandomBalance() noexcept {

    return rand() % (100000 - 10000 + 1) + 10000;  // Random balance between 10000 and 100000
}