
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include "../utilities.hpp"

namespace Day01 {

    std::vector<std::string> digitWords = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    std::vector<char> digitChars = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

    char GetLastCharPart2(const std::string& line) {
        std::size_t maxPos = 0;
        int value = -1;
        for (int i = 1; i < 10; i++) {
            auto charFound = line.rfind(digitChars[i]);
            if (charFound != std::string::npos && (charFound > maxPos or value < 0)) {
                maxPos = charFound;
                value = i;
            }
            auto wordFound = line.rfind(digitWords[i]);
            if (wordFound != std::string::npos && (wordFound > maxPos or value < 0)) {
                maxPos = wordFound;
                value = i;
            }
        }
        return digitChars[value];
    }

    char GetFirstCharPart2(const std::string& line) {
        std::size_t minPos = 0;
        int value = -1;
        for (int i = 1; i < 10; i++) {
            auto charFound = line.find(digitChars[i]);
            if (charFound != std::string::npos && (charFound < minPos or value < 0)) {
                minPos = charFound;
                value = i;
            }
            auto wordFound = line.find(digitWords[i]);
            if (wordFound != std::string::npos && (wordFound < minPos or value < 0)) {
                minPos = wordFound;
                value = i;
            }
        }
        return digitChars[value];
    }

    int solve() {

        std::vector<std::string> lines;
        Utilities::ReadFile("day01/input.txt", lines);

        {  // Part 1
            uint64_t sum = 0;
            for (const auto &line: lines) {
                char first = '-';
                char last;
                for (const auto &c: line) {
                    if (isnumber(c)) {
                        first = first != '-' ? first : c;
                        last = c;
                    }
                }
                std::stringstream ss;
                int num;
                ss << first << last;
                ss >> num;
                sum += num;
            }

            std::cout << "Answer 1 " << sum << std::endl;
        }

        {  // Part 2
            uint64_t sum = 0;
            for (const auto &line: lines) {
                std::stringstream ss;
                int num = 0;
                ss << GetFirstCharPart2(line) << GetLastCharPart2(line);
                ss >> num;
                sum += num;
            }

            std::cout << "Answer 2 " << sum << std::endl;
        }
        return 0;
    }
}