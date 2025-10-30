#include <filesystem>
#include <fstream>
#include <iostream>

// Number of characters in the output hash
#define OUTPUT_SIZE 64

// Define the used ASCII character range for the hash functions
#define ASCII_MIN_RANGE 0
#define ASCII_MAX_RANGE 255

// Define the maximum and minimum values for the incrementor used for the multiplier in hash functions
#define mIncrementor_MAX 100
#define mIncrementor_MIN 3


// Global incrementors used in the hash functions to add variability
size_t incrementor = 1;
size_t mIncrementor = mIncrementor_MIN;

// Concatenates two number (unsinged short) values
size_t concatenate(const unsigned short a, const unsigned short b)
{
    std::string result = std::to_string(a);
    result += std::to_string(b);
    return std::stoll(result);
}

// Increments the multiplier incrementor and resets it if it exceeds the maximum value
size_t multiplierIncrementor()
{
    if (++mIncrementor > mIncrementor_MAX)
    {
        mIncrementor = mIncrementor_MIN;
    }
    return mIncrementor;
}

// Part of the hash function. Takes one character and determanistically returns two random characters based on the input character and the incrementor
std::string splitChar(unsigned char target)
{
    std::string split;
    if (target < ASCII_MIN_RANGE)
    {
        target += ASCII_MIN_RANGE + ++incrementor;
    }

    split += static_cast<unsigned char>((target + ++incrementor - ASCII_MIN_RANGE) * 3 % (ASCII_MAX_RANGE - ASCII_MIN_RANGE + 1) + ASCII_MIN_RANGE);
    split += static_cast<unsigned char>((split.at(0) + ++incrementor - ASCII_MIN_RANGE) * 3 % (ASCII_MAX_RANGE - ASCII_MIN_RANGE + 1) + ASCII_MIN_RANGE);
    return split;
}

// Part of the hash function. Takes two characters and determanistacally returns one random character based on both input characters and the incrementor
unsigned char combineChars(unsigned const char a, unsigned const char b)
{
    auto position = concatenate(a, b);

    if (position < ASCII_MIN_RANGE)
    {
        position += ASCII_MIN_RANGE + ++incrementor;
    }

    return static_cast<unsigned char>((position + ++incrementor - ASCII_MIN_RANGE) * 3 % (ASCII_MAX_RANGE - ASCII_MIN_RANGE + 1) + ASCII_MIN_RANGE);
}

std::string readFile(std::string &&file_name)
{
    std::ifstream f(file_name);
    std::string out;

    if (!f.good())
    {
        std::cerr << "File is inaccessible" << std::endl;
        return "";
    }

    auto size = std::filesystem::file_size(file_name);
    out.resize(size, '\0');
    f.read(&out[0], size);
    return out;
}

int main(int argc, char **argv)
{
    // Test variables
    // argc = 3;
    // argv[1] = "l";
    // argv[2] = "Hello world";

    // First argument specifies the operatoin mode and the second one specifies the file
    // If there is only one argument it will assume it is operating in file mode and expect the first argument to be a file

    // This checks if there is a first argument
    if (argc < 2)
    {
        std::cerr << "Please specify operation mode, pass argument 'f' for file mode and argument 'l' for inline mode" << std::endl;
        return 1;
    }

    // The input variable is set as the string to be hashed, used as the intermediary for the hash function and is the outputed hashed
    std::string input;

    // Parse arguments
    if (argv[1] == "l")
    {
        if (argc < 3)
        {
            std::cerr << "Please input some text" << std::endl;
            return 1;
        }
        input = argv[2];
    }
    else if (argv[1] == "f")
    {
        if (argc < 3)
        {
            std::cerr << "Please input the filename" << std::endl;
            return 1;
        }
        input = readFile(std::string(argv[2]));
    }
    else
    {
        input = readFile(std::string(argv[1]));
    }

    // Can't hash an empty string
    if (input.size() == 0)
    {
        std::cerr << "Input is empty" << std::endl;
        return 1;
    }

    // Hash start

    // If the input is too small expand it to required size
    for (size_t i = 0; input.size() < OUTPUT_SIZE; i++)
    {
        auto split = splitChar(input.at(i));
        input.at(0) = split.at(0);
        input += split.at(1);
    }

    // Hash process from left to right
    input.at(0) = combineChars(input.at(0), input.at(1));
    for (size_t i = 1; i < input.size(); i++)
    {
        input.at(i) = combineChars(input.at(i - 1), input.at(i));
    }

    // Hash process from right to left
    for (size_t i = input.size() - 2; i > 0; i--)
    {
        input.at(i) = combineChars(input.at(i + 1), input.at(i));
    }
    input.at(0) = combineChars(input.at(0), input.at(1));

    // If the input is too large shrink it to required size
    for (size_t i = 0; input.size() > OUTPUT_SIZE; i++)
    {
        if (i >= input.size())
        {
            i = 0;
        }
        input.at(i) = combineChars(input.back(), input.at(i));
        input.pop_back();
    }
    

    // Result output
    for (auto c : input)
    {
        std::cout << std::hex << (static_cast<int>(c) + 128);
    }
    

    return 0;
}