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
        Utilities::ReadFile(name + "/example.txt", lines);
        Solve();
    }
private:
    std::vector<std::string> lines;

    enum Direction {
        Up, Down, Left, Right
    };

    struct State {
        int totalHeat;
        std::pair<int, int> pos;
        std::pair<int, int> prevStatePos;
        std::vector<Direction> directions;
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

    Direction GetDir(const std::pair<int, int>& newPos, const std::pair<int, int>& fromPos) {
        if (newPos.first > fromPos.first) return Direction::Down;
        if (newPos.first < fromPos.first) return Direction::Up;
        if (newPos.second > fromPos.second) return Direction::Right;
        if (newPos.second < fromPos.second) return Direction::Left;
        throw;
    };

    bool isValid(const std::pair<int, int>& newPos, const std::pair<int, int>& currPos, const std::pair<int, int>& prevState, const std::vector<Direction>& directions) {
        if (newPos.first == prevState.first && newPos.second == prevState.second)
            return false;

        auto newDir = GetDir(newPos, currPos);

        auto dirSize = directions.size();
        if (dirSize >= 3) {
            if (directions[dirSize-1] == newDir
                && directions[dirSize-2] == newDir
                && directions[dirSize-3] == newDir) {
                return false;
            }
        }

        return (newPos.first >= 0) && (newPos.first < nodeMap.size()) && (newPos.second >= 0) && (newPos.second < nodeMap[0].size());
    }

    class Compare {
    public:
        bool operator() (const State &a, const State& b) {
            return a.totalHeat < b.totalHeat;
        }
    };

    int calculateShortestWithDijkstra(int startRow, int startCol, int endRow, int endCol) {
        std::vector<std::vector<int>> minHeatMap(nodeMap.size(), std::vector<int>(nodeMap[0].size(), INT_MAX - 10000));

        std::priority_queue<State, std::vector<State>, Compare> pq;

        pq.push(State {0, {startRow, startCol}, {-10, -10}, {}});
        minHeatMap[startRow][startCol] = 0;

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
                if (!isValid(newPos, currentState.pos, currentState.prevStatePos, currentState.directions)) continue;
                int totalHeat = minHeatMap[currentState.pos.first][currentState.pos.second] + nodeMap[newPos.first][newPos.second];
                auto existingMinHeat = minHeatMap[newPos.first][newPos.second];
                if (totalHeat < existingMinHeat) {
                    minHeatMap[newPos.first][newPos.second] = totalHeat;
                    State newState;
                    newState.pos = newPos;
                    newState.totalHeat = totalHeat;
                    newState.prevStatePos = currentState.pos;
                    newState.directions = currentState.directions;
                    newState.directions.push_back(GetDir(newPos, currentState.pos));
                    pq.push(newState);
                }
            }
        }

        for (int i = 0; i < nodeMap.size(); ++i) {
            for (int j = 0; j < nodeMap[0].size(); ++j) {
                std::cout << minHeatMap[i][j] << " ";
            }
            std::cout << std::endl;
        }
        return minHeatMap[endRow][endCol];
    }
};
