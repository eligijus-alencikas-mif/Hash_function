#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>
#include <random>

size_t concatenate(size_t a, size_t b) {
    std::string result = std::to_string(a);
    result += std::to_string(b);
    return std::stoi(result);
}

size_t find_letter_pos(const char letter, const std::string& s) {
    for (size_t i = 0; i < s.size(); i++) {
        if (letter == s.at(i)) {
            return i;
        }
    }
    return 0;
}

std::string splitChar(const char a, const std::string& charOrder) {
    std::string split;
    for (size_t i = 0; i < charOrder.size(); i++) {
        if (a == charOrder.at(i)) {
            if (i != charOrder.size() - 1) {
                split += charOrder.at(i+1);
            }else {
                split += charOrder.at(i-2);
            }
            if (i != 0) {
                split += charOrder.at(i-1);
            }else {
                split += charOrder.at(i+2);
            }
        }
    }

    return split;
}

char combineChars(std::string split, const std::string& charOrder) {
    size_t l1_pos = find_letter_pos(split.at(0), charOrder) + 1;
    size_t l2_pos = find_letter_pos(split.at(1), charOrder) + 1;

    auto position = (concatenate(l1_pos, l2_pos)^2)/2;

    if (position + 1 > charOrder.size()) {
        position -= charOrder.size() * std::floor(position/charOrder.size());
    }

    return charOrder.at(position);
}

int main(int argc, char **argv) {
    std::string charOrder = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    if (argc < 2) {
        std::cerr << "Need an input" << std::endl;
        return 1;
    }
    const std::string input = argv[1];

    std::cout << "The input is: " << input << std::endl;
    std::cout << "Input length: " << input.size() << std::endl;

    std::string hash;
    for (const auto letter : input) {
        hash += splitChar(letter,charOrder);
    }

    {
        std::string comb;
        comb += hash.at(0);
        comb += hash.at(1);
        hash.at(0) = combineChars(comb, charOrder);
    }
    for (size_t i = 1; i < input.size(); i++) {
        std::string comb;
        comb += hash.at(i-1);
        comb += hash.at(i);

        hash.at(i) = combineChars(comb, charOrder);
    }

    for (size_t i = hash.length(); i > 0; i--) {
        std::string comb;
        comb += hash.at(i-1);

        if (i-1 == 0) {
            comb += hash.at(i);
        }else {
            comb += hash.at(i-2);
        }

        hash.at(i-1) = combineChars(comb, charOrder);
    }

    std::cout << "The hash: " << hash << std::endl;
    std::cout << "Hash length: " << hash.size() << std::endl;

    return 0;
}