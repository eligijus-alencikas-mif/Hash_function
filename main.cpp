#include <filesystem>
#include <fstream>
#include <iostream>

#define OUTPUT_SIZE 16

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

    split += static_cast<char>((target + ++incrementor - 33)*3 % 94 + 33);
    split += static_cast<char>((split.at(0) + ++incrementor - 33)*3 % 94 + 33);
    return split;
}

char combineChars(unsigned const char a, unsigned const char b) {
    auto position = concatenate(a, b);

    if (position < 33) {
        position += 33 + ++incrementor;
    }

    return static_cast<char>((position + ++incrementor - 33)*3 % 94 + 33);
}

int main(const int argc, char **argv) {
    if (argc < 2) {
        std::cerr << "Please specify operation mode, pass argument 'f' for file mode and argument 'l' for inline mode" << std::endl;
        return 1;
    }

    std::string input;

    std::string first_argument = argv[1];

    if (first_argument == "f") {
        if (argc < 3) {
            std::cerr << "Please specify a valid file" << std::endl;
            return 1;
        }
        std::ifstream f(argv[2]);
        if (!f.good()) {
            std::cerr << "File is inaccessible" << std::endl;
            return 1;
        }
        auto size = std::filesystem::file_size(argv[2]);
        input.resize(size, '\0');
        std::ifstream in(argv[2]);
        in.read(&input[0], size);
    }else if (first_argument == "l") {
        if (argc < 3) {
            std::cerr << "Please input some text" << std::endl;
            return 1;
        }
        input = argv[2];
    }else {
        std::cerr << "Incorrect argument" << std::endl;
        return 1;
    }

    for (size_t i = 0; input.size() < OUTPUT_SIZE; i++) {
        auto split = splitChar(input.at(i));
        input.at(0) = split.at(0);
        input += split.at(1);
    }

    input.at(0) = combineChars(input.at(0), input.at(1));
    for (size_t i = 1; i < input.size(); i++) {
        input.at(i) = combineChars(input.at(i-1), input.at(i));
    }

    for (size_t i = input.size() - 2; i > 0; i--) {
        input.at(i) = combineChars(input.at(i+1), input.at(i));
    }
    input.at(0) = combineChars(input.at(0), input.at(1));

    for (size_t i = 0; input.size() > OUTPUT_SIZE; i++) {
        if (i >= input.size()) {
            i = 0;
        }
        input.at(i) = combineChars(input.back(), input.at(i));
        input.pop_back();
    }

    std::cout << input;
    return 0;
}