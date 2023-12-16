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
        Utilities::ReadFile(name + "/input.txt", lines);
        Solve();
    }
private:
    std::vector<std::string> lines;

    struct Hotspring {
        std::string pattern;
        std::vector<int> blocks;
    };

    std::unordered_map<std::string, long> cache;

    void Solve() {
        {  // Part 1
            long long sum = 0;
            for (const auto& line : lines) {
                cache.clear();
                auto hotSpring = ParseToHotSpring(line, false);
                sum += Calculate(hotSpring.pattern, hotSpring.blocks);
            }
            std::cout << "Answer 1 " << sum << std::endl;
        }

        {  // Part 2
            long long sum = 0;
            for (const auto& line : lines) {
                auto hotSpring = ParseToHotSpring(line, true);
                sum += Calculate(hotSpring.pattern, hotSpring.blocks);
            }
            std::cout << "Answer 2 " << sum << std::endl;
        }
    }

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

    long long Calculate(const std::string& springs, const std::vector<int>& groups) {
        std::string key = springs + ",";
        for (int group : groups) {
            key += std::to_string(group) + ",";
        }

        auto it = cache.find(key);
        if (it != cache.end()) {
            return it->second;
        }

        long value = GetCount(springs, groups);
        cache[key] = value;

        return value;
    }

    long long GetCount(std::string springs, std::vector<int> groups) {
        while (true) {
            if (groups.empty()) {
                return springs.find('#') == std::string::npos ? 1 : 0;
            }

            if (springs.empty()) {
                return 0;
            }

            if (springs[0] == '.') {
                springs.erase(0, springs.find_first_not_of('.'));
                continue;
            }

            if (springs[0] == '?') {
                return Calculate("." + springs.substr(1), groups) + Calculate("#" + springs.substr(1), groups);
            }

            if (springs[0] == '#') {
                if (groups.empty()) {
                    return 0;
                }

                int groupSize = groups[0];
                if (springs.size() < groupSize) {
                    return 0;
                }

                if (springs.substr(0, groupSize).find('.') != std::string::npos) {
                    return 0;
                }

                if (groups.size() > 1) {
                    if (springs.size() < groupSize + 1 || springs[groupSize] == '#') {
                        return 0;
                    }

                    springs = springs.substr(groupSize + 1);
                    groups.erase(groups.begin());
                    continue;
                }

                springs = springs.substr(groupSize);
                groups.erase(groups.begin());
                continue;
            }
            throw;
        }
    }
};
