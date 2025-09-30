#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>
#include <random>

// static_cast<char>(((target + increment - 33) % 94)+ 33);

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
    split += static_cast<char>((split.at(0) + ++incrementor - 33)*3 % 94+ 33);
    return split;
}

// char combineChars(neChars(std::string split) {
//     size_t l1_pos = find_letter_pos(split.at(0), charOrder) + 1;
//     size_t l2_pos = find_letter_pos(split.at(1), charOrder) + 1;
//
//     auto position = (concatenate(l1_pos, l2_pos)^2)/2;
//
//     if (position + 1 > charOrder.size()) {
//         position -= charOrder.size() * std::floor(position/charOrder.size());
//     }
//
//     return charOrder.at(position);
// }

int main(int argc, char **argv) {

    std::cout << splitChar('a');
    std::cout << splitChar('a');
    std::cout << splitChar('a');

    // if (argc < 2) {
    //     std::cerr << "Need an input" << std::endl;
    //     return 1;
    // }
    // const std::string input = argv[1];
    //
    // std::cout << "The input is: " << input << std::endl;
    // std::cout << "Input length: " << input.size() << std::endl;
    //
    // std::string hash = input;
    // // for (const auto letter : input) {
    // //     hash += splitChar(letter,charOrder);
    // // }
    //
    // {
    //     std::string comb;
    //     comb += hash.at(0);
    //     comb += hash.at(1);
    //     hash.at(0) = combineChars(comb);
    // }
    // for (size_t i = 1; i < input.size(); i++) {
    //     std::string comb;
    //     comb += hash.at(i-1);
    //     comb += hash.at(i);
    //
    //     hash.at(i) = combineChars(comb);
    // }
    //
    // for (size_t i = hash.length(); i > 0; i--) {
    //     std::string comb;
    //     comb += hash.at(i-1);
    //
    //     if (i-1 == 0) {
    //         comb += hash.at(i);
    //     }else {
    //         comb += hash.at(i-2);
    //     }
    //
    //     hash.at(i-1) = combineChars(comb);
    // }
    //
    // std::cout << "The hash: " << hash << std::endl;
    // std::cout << "Hash length: " << hash.size() << std::endl;

    return 0;
}