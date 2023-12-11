#include <string>
#include <vector>
#include <set>
#include <unordered_map>
#include <iostream>
#include <sstream>
#include "../utilities.hpp"
#include <regex>
#include <algorithm>

class Day03 {
public:
    Day03() {
        std::string name = "day03";
        std::cout << name << std::endl;
        Utilities::ReadFile(name + "/input.txt", lines);
        Solve();
    }
private:
    std::vector<std::string> lines;

    void Solve() {
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
                    if (!isdigit(c) && c != '.')
                        AddRelevantNumbersIfCloseTo(i, j, engineMap, relevantNumbers);
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
                    if (c == '*')
                        sum += FetchRatioForGearAt(i, j, engineMap);
                    j++;
                }
                i++;
            }

            std::cout << "Answer 2 " << sum << std::endl;
        }
    }

private:

    typedef std::unordered_map<int, std::unordered_map<int, std::shared_ptr<int>>> MapOfNumbers;

    const std::vector<std::pair<int, int>> RelativeCorners = {
            {1,-1},{1,0},{1,1},
            {0,-1},{0,1},
            {-1,-1},{-1,0},{-1,1},
    };

    static std::unordered_map<int, std::shared_ptr<int>> ParseLineToMap(const std::string& line)
    {
        std::unordered_map<int, std::shared_ptr<int>> map;
        std::string tempNumber;
        std::shared_ptr<int> pointerToUniqueNumber = std::make_shared<int>();

        int i = 0;
        for (const auto& ch : line) {
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

    const std::shared_ptr<int>* GetValueIfExists(const MapOfNumbers& map,
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
        for (const auto& corner : RelativeCorners) {
            auto number = GetValueIfExists(map, symI + corner.first, symJ + corner.second);
            if (number != nullptr) {
                relevantNumbers.insert(*number);
            }
        }
    }

    int FetchRatioForGearAt(int symI, int symJ, const MapOfNumbers& map) {
        std::set<std::shared_ptr<int>> listOfRelevantNumbers;
        for (const auto& corner : RelativeCorners) {
            auto number = GetValueIfExists(map, symI+corner.first, symJ + corner.second);
            if (number == nullptr) continue;
            listOfRelevantNumbers.insert(*number);
            if (listOfRelevantNumbers.size() > 2) return 0;
        }
        if (listOfRelevantNumbers.size() != 2) return 0;
        return **listOfRelevantNumbers.begin() * **listOfRelevantNumbers.rbegin();
    }
};