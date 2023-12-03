#include <string>
#include <vector>
#include <set>
#include <iostream>
#include <sstream>
#include "../utilities_module.hpp"
#include <regex>

namespace Day03 {

    typedef std::map<int, std::map<int, std::shared_ptr<int>>> MapOfNumbers;

    std::map<int, std::shared_ptr<int>> ParseLineToMap(const std::string& line)
    {
        std::map<int, std::shared_ptr<int>> map;
        std::string tempNumber;
        std::shared_ptr<int> pointerToUniqueNumber = std::make_shared<int>();

        int i = 0;
        for (char ch : line) {
            if (isdigit(ch)) {
                tempNumber += ch;
                map.insert(std::make_pair(i, pointerToUniqueNumber));
            } else if (!tempNumber.empty()) {
                *pointerToUniqueNumber = stoi(tempNumber);
                pointerToUniqueNumber = std::make_shared<int>();
                tempNumber.clear();
            }
            i++;
        }
        if (!tempNumber.empty()) {
            *pointerToUniqueNumber = stoi(tempNumber);
        }

        return map;
    }

    const std::shared_ptr<int>* getValueIfExists(const MapOfNumbers& map,
                                const int& key1, const int& key2) {
        if (key1 < 0 || key2 < 0) {
            return nullptr;
        }
        auto it = map.find(key1);
        if (it != map.end()) {
            const auto& innerMap = it->second;
            const auto innerIt = innerMap.find(key2);
            if (innerIt != innerMap.end()) {
                return &innerIt->second;
            }
        }
        return nullptr;
    }

    void AddRelevantNumbersIfCloseTo(int symI, int symJ, const MapOfNumbers& map, std::set<std::shared_ptr<int>>& relevantNumbers) {
        for (int i = symI - 1; i <= symI + 1; i++) {
            for (int j = symJ - 1; j <= symJ + 1; j++) {
                auto number = getValueIfExists(map, i, j);
                if (number != nullptr) {
                    relevantNumbers.insert(*number);
                }
            }
        }
    }

    int FetchRatioForGearAt(int symI, int symJ, const MapOfNumbers& map) {
        std::set<std::shared_ptr<int>> listOfRelevantNumbers;
        for (int i = symI - 1; i <= symI + 1; i++) {
            for (int j = symJ - 1; j <= symJ + 1; j++) {
                auto number = getValueIfExists(map, i, j);
                if (number == nullptr) continue;
                listOfRelevantNumbers.insert(*number);
                if (listOfRelevantNumbers.size() > 2) return 0;
            }
        }
        if (listOfRelevantNumbers.size() != 2) return 0;
        return **listOfRelevantNumbers.begin() * **listOfRelevantNumbers.rbegin();
    }

    int solve() {

        std::vector<std::string> lines;
        Utilities::ReadFile("day03/input.txt", lines);
        MapOfNumbers engineMap;

        int lineNumber = 0;
        for (const auto& line : lines) {
            engineMap.insert(std::make_pair(lineNumber++, ParseLineToMap(line)));
        }

        {  // Part 1
            int i = 0;
            std::set<std::shared_ptr<int>> relevantNumbers;
            for (const auto& line : lines) {
                int j = 0;
                for (const auto& c : line) {
                    if (!isdigit(c) && c != '.') {
                        AddRelevantNumbersIfCloseTo(i, j, engineMap, relevantNumbers);
                    }
                    j++;
                }
                i++;
            }

            int sum = 0;
            for (const auto& num : relevantNumbers) {
                sum += *num;
            }

            std::cout << "Answer 1 " << sum << std::endl;
        }

        {  // Part 2
            int i = 0;
            int sum = 0;
            for (const auto& line : lines) {
                int j = 0;
                for (const auto& c : line) {
                    if (c == '*') {
                        sum += FetchRatioForGearAt(i, j, engineMap);
                    }
                    j++;
                }
                i++;
            }

            std::cout << "Answer 2 " << sum << std::endl;
        }

        return 0;
    }
}
