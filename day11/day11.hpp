#include <ranges>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <list>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <ranges>
#include <string_view>
#include "../utilities.hpp"

class Day11 {
public:
    Day11() {
        std::string name = "day11";
        std::cout << name << std::endl;
        Utilities::ReadFile(name + "/input.txt", lines);
        Solve();
    }
private:
    std::vector<std::string> lines;
    std::vector<std::pair<int, int>> space;
    std::unordered_set<int> iWithGalaxy;
    std::unordered_set<int> jWithGalaxy;

    void Solve() {
        ParseLinesToSpace();
        long long sum1 = 0;
        long long sum2 = 0;
        long long factor1 = 2;
        long long factor2 = 1000000;
        for (int it = 0; it < space.size(); it++) {
            for (int it2 = it+1; it2 < space.size(); it2++) {
                const auto& from = space[it];
                const auto& to = space[it2];
                const auto& empties = numberOfEmpties(from, to);
                const auto& diff = std::abs(from.first - to.first) + std::abs(from.second - to.second);
                sum1 += (diff + (empties*(factor1-1)));
                sum2 += (diff + (empties*(factor2-1)));
            }
        }
        std::cout << "Answer 1 " << sum1 << std::endl;
        std::cout << "Answer 2 " << sum2 << std::endl;
    }

    void ParseLinesToSpace() {
        for (int i = 0; i < lines.size(); i++) {
            for (int j = 0; j < lines[i].size();j++){
                if (lines[i][j] == '#') {
                    space.emplace_back(i, j);
                    iWithGalaxy.insert(i);
                    jWithGalaxy.insert(j);
                }
            }
        }
    }

    long long numberOfEmpties(const std::pair<int, int>& p1, const std::pair<int, int>& p2) {
        long long emptySpaces = 0;
        for (int i = std::min(p1.first, p2.first) + 1; i < std::max(p1.first, p2.first); i++) {
            if (iWithGalaxy.find(i) == iWithGalaxy.end()) {
                emptySpaces++;
            }
        }
        for (int j = std::min(p1.second, p2.second) + 1; j < std::max(p1.second, p2.second); j++) {
            if (jWithGalaxy.find(j) == jWithGalaxy.end()) {
                emptySpaces++;
            }
        }
        return emptySpaces;
    };
};
