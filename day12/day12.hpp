#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <list>
#include <algorithm>
#include <iostream>
#include <sstream>
#include "../utilities.hpp"

class Day12 {
public:
    Day12() {
        std::string name = "day12";
        std::cout << name << std::endl;
        Utilities::ReadFile(name + "/example.txt", lines);
        Solve();
    }
private:
    std::vector<std::string> lines;

    struct Hotspring {
        std::string pattern;
        std::vector<int> blocks;
    };


    typedef std::map<int, std::map<int, std::map<int, long long>>> MemMap;
    MemMap memoizationTable;

    long long GetValueIfExists(int key1, int key2, int key3) {
        if (key1 < 0 || key2 < 0 || key3 < 0) {
            return -1;
        }
        auto map1 = memoizationTable.find(key1);
        if (map1 != memoizationTable.end()) {
            const auto map2 = map1->second.find(key2);
            if (map2 != map1->second.end()) {
                const auto map3 = map2->second.find(key3);
                if (map3 != map2->second.end()) {
                    return map3->second;
                }
            }
        }
        return -1;
    }


    void Solve() {
        {  // Part 1
            long long sum = 0;
            for (const auto& line : lines) {
                memoizationTable.clear();
                auto hotSpring = ParseToHotSpring(line, false);
                sum += CountWaysToArrange(hotSpring.pattern, hotSpring.blocks, 0, 0, 0);
            }
            std::cout << "Answer 1 " << sum << std::endl;
        }

        {  // Part 2
            long long sum = 0;
            for (const auto& line : lines) {
                memoizationTable.clear();
                auto hotSpring = ParseToHotSpring(line, true);
                sum += CountWaysToArrange(hotSpring.pattern, hotSpring.blocks, 0, 0, 0);
            }
            std::cout << "Answer 2 " << sum << std::endl;
        }
    }

    long long CountWaysToArrange(const std::string& pattern, const std::vector<int>& blocks, int patIt, int biIt, int current) {

        auto memValue = GetValueIfExists(patIt, biIt, current);

        if (memValue != -1)
            return memValue;

        if (patIt >= pattern.size()) {
            if (biIt >= blocks.size() && current == 0) {
                return 1;
            } else if (biIt >= blocks.size() - 1 && blocks[biIt] == current) {
                return 1;
            } else {
                return 0;
            }
        }

        long long sum = 0;
        for (const auto& replaceWith : ReplaceWith) {
            auto c = pattern[patIt];
            if (c == '?' || c == replaceWith) {
                if (c == '.' && current == 0)
                    sum += CountWaysToArrange(pattern, blocks, patIt + 1, biIt, 0);
                else if (c == '.' && current > 0 && biIt < blocks.size() && blocks[biIt] == current)
                    sum += CountWaysToArrange(pattern, blocks, patIt + 1, biIt + 1, 0);
                else if (c == '#')
                    sum += CountWaysToArrange(pattern, blocks, patIt + 1, biIt, current + 1);
            }
        }
        memoizationTable[patIt][biIt][current] = sum;
        return sum;
    }

    const std::vector<char> ReplaceWith = {'.', '#'};

    static Hotspring ParseToHotSpring(const std::string& line, bool expanded) {
        Hotspring in;
        auto space = line.find(' ');
        in.pattern = line.substr(0, space);
        auto rest = line.substr(space + 1);
        std::vector<int> numbers;
        std::stringstream ss(Utilities::Trim(rest));
        std::string token;

        while (getline(ss, token, ',')) {
            in.blocks.push_back(stoi(token));
        }

        if (expanded) {
            auto orig_pattern = in.pattern;
            auto orig_damaged = in.blocks;
            for (int i = 0; i < 4; ++i) {
                in.pattern += '?';
                in.pattern += orig_pattern;
                in.blocks.insert(in.blocks.end(), orig_damaged.begin(), orig_damaged.end());
            }
        }
        in.pattern += '.';
        return in;
    }
};
