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

class Day14 {
public:
    Day14() {
        std::string name = "day14";
        std::cout << name << std::endl;
        Utilities::ReadFile(name + "/input.txt", lines);
        Solve();
    }
private:
    std::vector<std::string> lines;
    std::vector<std::vector<char>> worldMap;

    void Solve() {
        for (auto& line : lines) {
            std::vector<char> tmp;
            for (auto& ch : line) {
                tmp.push_back(ch);
            }
            worldMap.push_back(tmp);
        }

        {  // Part 1
            MoveAllNorth();
            auto weight = CalculateWeightNorth();
            std::cout << "Answer 1 " << weight << std::endl;
        }
        worldMap.clear();

        for (auto& line : lines) {
            std::vector<char> tmp;
            for (auto& ch : line) {
                tmp.push_back(ch);
            }
            worldMap.push_back(tmp);
        }

        {  // Part 2
            std::map<long long, std::pair<std::pair<int, int>, std::pair<int, int>>> weights;
            for (int i = 0; i < 200; i++) {
                Cycle();
                long long weight = CalculateWeightNorth();
                if (weights.contains(weight)) {
                    weights[weight].first.first++;
                    weights[weight].second.first = weights[weight].second.second;
                    weights[weight].second.second = i;
                } else {
                    weights[weight] = std::make_pair(std::make_pair(1, i-1), std::make_pair(i, i));
                }
            }

            const int target = 1000000000;
            long long result = 0;
            for (auto& weight : weights) {
                if (weight.second.first.first > 10) {
                    if ((target - weight.second.first.second) % (weight.second.second.second - weight.second.second.first) == 0) {
                        result = weight.first;
                    }
                }
            }

            std::cout << "Answer 2 " << result << std::endl;
        }
    }

    long long CalculateWeightNorth() {
        long long weight = 0;
        for (int i = 0; i < worldMap[0].size(); i++) {
            for (int j = 0; j < worldMap.size(); j++) {
                auto currChar = worldMap[j][i];
                if (currChar == 'O') {
                    weight += (worldMap.size() -j);
                }
            }
        }
        return weight;
    }
    void PrintAll() {
        for (int i = 0; i < worldMap.size(); i++) {
            for (int j = 0; j < worldMap[0].size(); j++) {
                std::cout << worldMap[i][j];
            }
            std::cout << std::endl;
        }
    }

    void Cycle() {
        MoveAllNorth();
        MoveAllWest();
        MoveAllSouth();
        MoveAllEast();
    }

    void MoveAllNorth() {
        for (int i = 0; i < worldMap[0].size(); i++) {
            int lastOpenPos = -1;
            for (int j = 0; j < worldMap.size(); j++) {
                auto currChar = worldMap[j][i];
                if (currChar == '.') {
                    lastOpenPos = j;
                    continue;
                } else if (currChar == 'O') {
                    if (lastOpenPos >= 0) {
                        worldMap[j][i] = '.';
                        worldMap[lastOpenPos][i] = 'O';
                        j = -1;
                        lastOpenPos = -1;
                    }
                } else if (currChar == '#') {
                    lastOpenPos = -1;
                }
            }
        }
    }

    void MoveAllWest() {
        for (auto & j : worldMap) {
            int lastOpenPos = -1;
            for (int i = 0; i < j.size(); i++) {
                auto currChar = j[i];
                if (currChar == '.') {
                    lastOpenPos = i;
                    continue;
                } else if (currChar == 'O') {
                    if (lastOpenPos >= 0) {
                        j[i] = '.';
                        j[lastOpenPos] = 'O';
                        i = -1;
                        lastOpenPos = -1;
                    }
                } else if (currChar == '#') {
                    lastOpenPos = -1;
                }
            }
        }
    }

    void MoveAllSouth() {
        for (int i = 0; i < worldMap[0].size(); i++) {
            int lastOpenPos = -1;
            for (int j = worldMap.size() - 1; j >= 0; j--) {
                auto currChar = worldMap[j][i];
                if (currChar == '.') {
                    lastOpenPos = j;
                    continue;
                } else if (currChar == 'O') {
                    if (lastOpenPos >= 0) {
                        worldMap[j][i] = '.';
                        worldMap[lastOpenPos][i] = 'O';
                        j = worldMap.size(); // Restart scanning from the top of the column
                        lastOpenPos = -1;
                    }
                } else if (currChar == '#') {
                    lastOpenPos = -1;
                }
            }
        }
    }

    void MoveAllEast() {
        for (auto & j : worldMap) {
            int lastOpenPos = -1;
            for (int i = j.size() - 1; i >= 0; i--) {
                auto currChar = j[i];
                if (currChar == '.') {
                    lastOpenPos = i;
                    continue;
                } else if (currChar == 'O') {
                    if (lastOpenPos >= 0) {
                        j[i] = '.';
                        j[lastOpenPos] = 'O';
                        i = j.size(); // Restart scanning from the left of the row
                        lastOpenPos = -1;
                    }
                } else if (currChar == '#') {
                    lastOpenPos = -1;
                }
            }
        }
    }
};
