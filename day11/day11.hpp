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
                auto from = space[it];
                auto to = space[it2];
                auto empties = numberOfEmpties(from.first, to.first, from.second, to.second);
                auto diff = std::abs(from.first - to.first) + std::abs(from.second - to.second);
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

    long long numberOfEmpties(int i1, int i2, int j1, int j2) {
        long long emptySpaces = 0;
        if (i1 > i2) {
            int tmp = i2;
            i2 = i1;
            i1 = tmp;
        }
        for (int i = i1 + 1; i < i2; i++) {
            if (iWithGalaxy.find(i) == iWithGalaxy.end()) {
                emptySpaces++;
            }
        }
        if (j1 > j2) {
            int tmp = j2;
            j2 = j1;
            j1 = tmp;
        }
        for (int j = j1 + 1; j < j2; j++) {
            if (jWithGalaxy.find(j) == jWithGalaxy.end()) {
                emptySpaces++;
            }
        }
        return emptySpaces;
    };
};
