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

            std::cout << "Before---" << std::endl;
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
            std::map<long long, int> weights;
            for (int i = 0; i < 1000; i++) {
                Cycle();
                long long weight = CalculateWeightNorth();
                if (weights.contains(weight)) {
                    weights[weight]++;
                } else {
                    weights[weight] = 1;
                }
            }
            std::cout << "Answer 2 " << 0 << std::endl;
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
        for (int j = 0; j < worldMap.size(); j++) {
            int lastOpenPos = -1;
            for (int i = 0; i < worldMap[j].size(); i++) {
                auto currChar = worldMap[j][i];
                if (currChar == '.') {
                    lastOpenPos = i;
                    continue;
                } else if (currChar == 'O') {
                    if (lastOpenPos >= 0) {
                        worldMap[j][i] = '.';
                        worldMap[j][lastOpenPos] = 'O';
                        i = -1;  // Restart scanning from the beginning of the row
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
        for (int j = 0; j < worldMap.size(); j++) {
            int lastOpenPos = -1;
            for (int i = worldMap[j].size() - 1; i >= 0; i--) {
                auto currChar = worldMap[j][i];
                if (currChar == '.') {
                    lastOpenPos = i;
                    continue;
                } else if (currChar == 'O') {
                    if (lastOpenPos >= 0) {
                        worldMap[j][i] = '.';
                        worldMap[j][lastOpenPos] = 'O';
                        i = worldMap[j].size(); // Restart scanning from the left of the row
                        lastOpenPos = -1;
                    }
                } else if (currChar == '#') {
                    lastOpenPos = -1;
                }
            }
        }
    }



};
