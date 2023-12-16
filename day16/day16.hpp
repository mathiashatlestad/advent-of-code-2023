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

class Day16 {
public:
    Day16() {
        std::string name = "day16";
        std::cout << name << std::endl;
        Utilities::ReadFile(name + "/input.txt", lines);
        Solve();
    }
private:
    std::vector<std::string> lines;

    enum Direction {
        Up, Down, Left, Right
    };

    struct Node {
        char type;
        int i,j;
        std::vector<Direction> VisitedDirections;
    };

    std::vector<std::vector<std::shared_ptr<Node>>> nodeMap;

    void Solve() {

        for (int i = 0; i < lines.size(); i++) {
            std::vector<std::shared_ptr<Node>> tmp;
            for (int j = 0; j < lines[0].size(); j++) {
                auto nd = std::make_shared<Node>();
                nd->i = i;
                nd->j = j;
                nd->type = lines[i][j];
                tmp.push_back(nd);
            }
            nodeMap.push_back(tmp);
        }

        {  // Part 1
            HandleLightBeam(nodeMap[0][0], Right);
            int sum = CountEnergized();
            std::cout << "Answer 1 " << sum << std::endl;
        }

        {  // Part 2
            auto lastJ = nodeMap[0].size() - 1;
            auto lastI = nodeMap.size()-1;
            int max = 0;
            for (int j = 0; j < nodeMap[0].size(); j++) {
                auto count = HandleAndPopulateP2(nodeMap[0][j], Down);
                max = std::max(max, count);
            }
            for (int i = 0; i < nodeMap.size(); i++) {
                auto count = HandleAndPopulateP2(nodeMap[i][lastJ], Left);
                max = std::max(max, count);
            }
            for (int j = 0; j < nodeMap[0].size(); j++) {
                auto count = HandleAndPopulateP2(nodeMap[lastI][j], Up);
                max = std::max(max, count);
            }
            for (int i = 0; i < nodeMap.size(); i--) {
                auto count = HandleAndPopulateP2(nodeMap[i][0], Right);
                max = std::max(max, count);
            }

            std::cout << "Answer 2 " << max << std::endl;
        }
    }

    int HandleAndPopulateP2(std::shared_ptr<Node> node, Direction dir) {
        ClearMap();
        HandleLightBeam(node, dir);
        return CountEnergized();
    }

    void HandleLightBeam(const std::shared_ptr<Node>& node, Direction dir) {
        if (node == nullptr) {
            return;
        }

        if (std::find(node->VisitedDirections.begin(), node->VisitedDirections.end(), dir) != node->VisitedDirections.end()) {
            return;
        }
        node->VisitedDirections.push_back(dir);

        for (auto& newDir : DirectionsFrom(node, dir)) {
           HandleLightBeam(FindNodeInDirection(node, newDir), newDir);
        }
    }

    std::shared_ptr<Node> FindNodeInDirection(const std::shared_ptr<Node>& node, Direction dir) {
        switch (dir) {
            case Up:
                if (node->i == 0) return nullptr;
                return nodeMap[node->i-1][node->j];
            case Down:
                if (node->i >= nodeMap.size() - 1) return nullptr;
                return nodeMap[node->i+1][node->j];
            case Left:
                if (node->j == 0) return nullptr;
                return nodeMap[node->i][node->j - 1];
            case Right:
                if (node->j >= nodeMap[0].size() - 1) return nullptr;
                return nodeMap[node->i][node->j+1];
        }
        return nullptr;
    }

    std::vector<Direction> DirectionsFrom(std::shared_ptr<Node> node, Direction dir) {
        switch (node->type) {
            case '.':
                return {dir};
            case '/': {
                switch (dir) {
                    case Up:
                        return {Right};
                    case Right:
                        return {Up};
                    case Left:
                        return {Down};
                    case Down:
                        return {Left};
                }
            }
            case '\\': {
                switch (dir) {
                    case Up:
                        return {Left};
                    case Right:
                        return {Down};
                    case Left:
                        return {Up};
                    case Down:
                        return {Right};
                }
            }
            case '-': {
                switch (dir) {
                    case Up:
                    case Down:
                        return {Left, Right};
                    case Right:
                    case Left:
                        return {dir};
                }
            }
            case '|': {
                switch (dir) {
                    case Right:
                    case Left:
                        return {Up, Down};
                    case Up:
                    case Down:
                        return {dir};
                }
            }
        }
        return {};
    }

    void ClearMap() {
        for (int i = 0; i < nodeMap.size(); i++) {
            for (int j = 0; j < nodeMap[0].size();j++) {
                nodeMap[i][j]->VisitedDirections.clear();
            }
        }
    }
    int CountEnergized() {
        int sum = 0;
        for (int i = 0; i < nodeMap.size(); i++) {
            for (int j = 0; j < nodeMap[0].size();j++) {
                if (nodeMap[i][j]->VisitedDirections.empty())
                    continue;
                sum++;
            }
        }
        return sum;
    }
};
