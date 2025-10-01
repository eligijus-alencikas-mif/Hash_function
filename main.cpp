#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>
#include <random>

size_t incrementor = 1;

size_t concatenate(size_t a, size_t b) {
    std::string result = std::to_string(a);
    result += std::to_string(b);
    return std::stoi(result);
}

std::string splitChar(char target) {
    std::string split;
    if (target < 33) {
        target += 33 + ++incrementor;
    }

    split += static_cast<char>((target + ++incrementor - 33)*3 % 94 + 33);
    split += static_cast<char>((split.at(0) + ++incrementor - 33)*3 % 94 + 33);
    return split;
}

char combineChars(const char a, const char b) {
    const auto position = concatenate(a, b);

    return static_cast<char>((position + ++incrementor - 33)*3 % 94 + 33);
}

int main(int argc, char **argv) {
    if (argc < 2) {
        std::cerr << "Need an input" << std::endl;
        return 1;
    }
    const std::string input = argv[1];

    std::cout << "The input is: " << input << std::endl;
    std::cout << "Input length: " << input.size() << std::endl;

    std::string hash = input;


    hash.at(0) = combineChars(hash.at(0), hash.at(1));
    for (size_t i = 1; i < input.size(); i++) {
        hash.at(i) = combineChars(hash.at(i-1), hash.at(i));
    }

    for (size_t i = input.size() - 2; i > 0; i--) {
        hash.at(i) = combineChars(hash.at(i+1), hash.at(i));
    }
    hash.at(0) = combineChars(hash.at(0), hash.at(1));

    std::cout << "The hash: " << hash << std::endl;
    std::cout << "Hash length: " << hash.size() << std::endl;

    return 0;
}