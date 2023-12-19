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

class Day17 {
public:
    Day17() {
        std::string name = "day17";
        std::cout << name << std::endl;
        Utilities::ReadFile(name + "/input.txt", lines);
        Solve();
    }
private:
    std::vector<std::string> lines;

    enum Direction {
        Up = 1, Down = 2, Left = 3, Right = 4
    };

    struct State {
        int totalHeatLoss;
        std::pair<int, int> pos;
        std::pair<int, int> prevStatePos;
        Direction direction;
        int stepsInDir;
        std::vector<std::pair<int, int>> prevPositions;
    };

    typedef std::vector<std::vector<int>> NodeMap;
    NodeMap nodeMap;

    void Solve() {

        for (int i = 0; i < lines.size(); i++) {
            std::vector<int> tmp;
            tmp.reserve(lines[0].size());
            for (int j = 0; j < lines[0].size(); j++) {
                tmp.push_back(int(lines[i][j] - '0'));
            }
            nodeMap.push_back(tmp);
        }

        {  // Part 1
            int ans = 0;
            ans = calculateShortestWithDijkstra(0,0,nodeMap.size()-1, nodeMap[0].size() -1);
            if (ans == 1355) {
                std::cout << "WRONG!" << std::endl;
            }
            std::cout << "Answer 1: " << ans << std::endl;
        }

        {  // Part 2
            int ans = 0;
            std::cout << "Answer 2: " << ans << std::endl;
        }
    }

    static Direction GetDir(const std::pair<int, int>& newPos, const std::pair<int, int>& fromPos) {
        if (newPos.first > fromPos.first) return Direction::Down;
        if (newPos.first < fromPos.first) return Direction::Up;
        if (newPos.second > fromPos.second) return Direction::Right;
        if (newPos.second < fromPos.second) return Direction::Left;
        throw;
    };

    bool isValid(const std::pair<int, int>& newPos, const std::pair<int, int>& currPos, const std::pair<int, int>& prevPos, const Direction& prevDir, int stepsInDir, const std::vector<std::pair<int, int>> allPos) {
        if (newPos == prevPos) return false;
        if (std::find(allPos.begin(), allPos.end(), std::make_pair(int(nodeMap.size() - 1), int(nodeMap[0].size()-1))) != allPos.end()) return false;
        if (std::find(allPos.begin(), allPos.end(), newPos) != allPos.end()) return false;

        auto newDir = GetDir(newPos, currPos);
        if (newDir == prevDir) {
            if (stepsInDir >= 10) {
                return false;
            }
        } else if (allPos.size() < 3) {
            if (newDir != prevDir)
                return false;
        } else if (stepsInDir < 4 && allPos.size() >= 4) {
            return false;
        }

        return (newPos.first >= 0) && (newPos.first < nodeMap.size()) && (newPos.second >= 0) && (newPos.second < nodeMap[0].size());
    }

    class Compare {
    public:
        bool operator() (const State &a, const State& b) {
            return a.totalHeatLoss > b.totalHeatLoss;
        }
    };

    int calculateShortestWithDijkstra(int startRow, int startCol, int endRow, int endCol) {
        std::vector<std::vector<std::vector<std::vector<int>>>> minHeatMap(nodeMap.size(), std::vector(nodeMap[0].size(), std::vector(5, std::vector(11, INT_MAX - 10000))));

        std::priority_queue<State, std::vector<State>, Compare> pq;

        pq.push(State {0, {startRow, startCol}, {startRow, startCol}, Down, 0, {{startRow, startCol}}});
        pq.push(State {0, {startRow, startCol}, {startRow, startCol}, Right, 0, {{startRow, startCol}}});

        minHeatMap[startRow][startCol][0][0] = 0;

        std::vector<std::pair<int, int>> explore {
                {-1, 0},
                {1, 0},
                {0, 1},
                {0, -1},
        };

        State endState;
        endState.totalHeatLoss = INT32_MAX;

        while (!pq.empty()) {
            auto currentState = pq.top();
            pq.pop();

            if (currentState.pos.first == endRow
            && currentState.pos.second == endCol
            && endState.totalHeatLoss > currentState.totalHeatLoss
            && currentState.stepsInDir >= 4) {
                endState = currentState;
                break;
            }

            for (auto& exp : explore) {
                auto newPos = std::make_pair(currentState.pos.first + exp.first, currentState.pos.second + exp.second);
                if (!isValid(newPos, currentState.pos, currentState.prevStatePos, currentState.direction, currentState.stepsInDir, currentState.prevPositions)) {
                    continue;
                }

                auto newDir = GetDir(newPos, currentState.pos);
                auto stepsInDir = newDir == currentState.direction ? currentState.stepsInDir + 1 : 1;
                int totalHeat = currentState.totalHeatLoss + nodeMap[newPos.first][newPos.second];
                auto existingMinHeat = minHeatMap[newPos.first][newPos.second][newDir][stepsInDir];

                if (totalHeat > endState.totalHeatLoss) {
                    continue;
                }

                if (totalHeat < existingMinHeat) {
                    minHeatMap[newPos.first][newPos.second][newDir][stepsInDir] = totalHeat;
                    State newState;
                    newState.pos = newPos;
                    newState.totalHeatLoss = totalHeat;
                    newState.prevStatePos = currentState.pos;
                    newState.direction = newDir;
                    newState.stepsInDir = stepsInDir;
                    newState.prevPositions = currentState.prevPositions;
                    newState.prevPositions.push_back(newPos);
                    pq.push(newState);
                }
            }
        }

        for (int i = 0; i < nodeMap.size(); ++i) {
            for (int j = 0; j < nodeMap[0].size(); ++j) {
                if (std::find(endState.prevPositions.begin(), endState.prevPositions.end(), std::make_pair(i, j)) != endState.prevPositions.end()) {
                    std::cout << "'" << nodeMap[i][j] << "\t\t";
                } else {
                    std::cout << nodeMap[i][j] << "\t\t";
                }
            }
            std::cout << std::endl;
        }

        return endState.totalHeatLoss;
    }
};
