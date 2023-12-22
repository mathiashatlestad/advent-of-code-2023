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
#include <queue>

class Day21 {
public:
    Day21() {
        std::string name = "day21";
        std::cout << name << std::endl;
        Utilities::ReadFile(name + "/input.txt", lines);
        Solve();
    }
private:
    std::vector<std::string> lines;

    struct State {
        int steps = 0;
        std::pair<int, int> pos;
    };

    typedef std::vector<std::vector<char>> NodeMap;
    NodeMap nodeMap;

    std::pair<int, int> startPos;

    void Solve() {

        for (int i = 0; i < lines.size(); i++) {
            std::vector<char> tmp;
            tmp.reserve(lines[0].size());
            for (int j = 0; j < lines[0].size(); j++) {
                tmp.push_back(lines[i][j]);
                if (lines[i][j] == 'S') {
                    startPos.first = i;
                    startPos.second = j;
                }
            }
            nodeMap.push_back(tmp);
        }

        {  // Part 1
            long long ans = 0;
            int desiredSteps = 64;
            auto minStepMap = calculateShortestWithDijkstra(startPos.first,startPos.second, desiredSteps);
            for (auto& row : minStepMap) {
                for (auto& col : row) {
                    if (col == desiredSteps) {
                        ans++;
                    } else if (col <= desiredSteps && col % 2 == 0) {
                        ans++;
                    }
                }
            }
            std::cout << "Answer 1: " << ans << std::endl;
        }

        {  // Part 2
            int ans = 0;
            std::cout << "Answer 2: " << ans << std::endl;
        }
    }

    bool isValid(const std::pair<int, int>& newPos) {
        return (newPos.first >= 0) && (newPos.first < nodeMap.size()) && (newPos.second >= 0) && (newPos.second < nodeMap[0].size());
    }

    class Compare {
    public:
        bool operator() (const State &a, const State& b) {
            return a.steps > b.steps;
        }
    };

    std::vector<std::vector<int>> calculateShortestWithDijkstra(int startRow, int startCol, int stepsWanted) {
        std::vector<std::vector<int>> minStepMap(nodeMap.size(), std::vector(nodeMap[0].size(), INT_MAX));

        std::priority_queue<State, std::vector<State>, Compare> pq;

        pq.push(State {0, {startRow, startCol}});

        minStepMap[startRow][startCol] = 0;

        std::vector<std::pair<int, int>> explore {
                {-1, 0},
                {1, 0},
                {0, 1},
                {0, -1},
        };

        while (!pq.empty()) {
            auto currentState = pq.top();
            pq.pop();

            for (auto& exp : explore) {
                auto newPos = std::make_pair(currentState.pos.first + exp.first, currentState.pos.second + exp.second);
                if (!isValid(newPos)) {
                    continue;
                }

                if (nodeMap[newPos.first][newPos.second] == '#') continue;

                int totalSteps = currentState.steps + 1;
                auto existingMinHeat = minStepMap[newPos.first][newPos.second];

                if (totalSteps > stepsWanted)
                    continue;

                if (existingMinHeat > totalSteps) {
                    minStepMap[newPos.first][newPos.second] = totalSteps;
                    State newState{};
                    newState.pos = newPos;
                    newState.steps = totalSteps;
                    pq.push(newState);
                }
            }
        }

        return minStepMap;
    }
};

