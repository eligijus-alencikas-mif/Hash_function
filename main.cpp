#include <iostream>

size_t incrementor = 1;

size_t concatenate(const unsigned short a, const unsigned short b) {
    std::string result = std::to_string(a);
    result += std::to_string(b);
    return std::stoll(result);
}

std::string splitChar(unsigned char target) {
    std::string split;
    if (target < 33) {
        target += 33 + ++incrementor;
    }

    split += static_cast<unsigned char>((target + ++incrementor - 33)*3 % 94 + 33);
    split += static_cast<unsigned char>((split.at(0) + ++incrementor - 33)*3 % 94 + 33);
    return split;
}

char combineChars(unsigned const char a, unsigned const char b) {
    const auto position = concatenate(a, b);

    return static_cast<unsigned char>((position + ++incrementor - 33)*3 % 94 + 33);
}

int main(const int argc, char **argv) {
    if (argc < 2) {
        std::cerr << "Need an input" << std::endl;
        return 1;
    }
    std::string input = argv[1];

    std::cout << "The input is: " << input << std::endl;
    std::cout << "Input length: " << input.size() << std::endl;

    input.at(0) = combineChars(input.at(0), input.at(1));
    for (size_t i = 1; i < input.size(); i++) {
        input.at(i) = combineChars(input.at(i-1), input.at(i));
    }

    for (size_t i = input.size() - 2; i > 0; i--) {
        input.at(i) = combineChars(input.at(i+1), input.at(i));
    }
    input.at(0) = combineChars(input.at(0), input.at(1));

    std::cout << "The hash: " << input << std::endl;
    std::cout << "Hash length: " << input.size() << std::endl;

    return 0;
}