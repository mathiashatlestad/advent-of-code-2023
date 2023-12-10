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

class Day10 {
public:
    Day10() {
        std::string name = "day10";
        std::cout << name << std::endl;
        Utilities::ReadFile(name + "/input.txt", lines);
        Solve();
    }
private:
    std::vector<std::string> lines;

    struct Node {
        int x, y;
        char nodeType;
        bool isPartOfLoop = false;
        std::shared_ptr<Node> pipeTo;
        std::shared_ptr<Node> pipeFrom;
    };

    typedef std::map<int, std::map<int, std::shared_ptr<Node>>> Nodes;
    Nodes nodes;

    std::shared_ptr<Node> startNode;
    std::vector<std::shared_ptr<Node>> loopNodes;
    std::vector<std::shared_ptr<Node>> allNodes;

    void Solve() {
        PopulateNodesMap();

        {  // Part 1
            auto currNode = startNode;
            auto prevNode = startNode;
            int count = 0;
            while (currNode != startNode || count == 0) {
                currNode->isPartOfLoop = true;
                loopNodes.push_back(currNode);
                auto nextNode = prevNode != currNode->pipeFrom ? currNode->pipeFrom : currNode->pipeTo;
                prevNode = currNode;
                currNode = nextNode;
                count++;
            }
            std::cout << "Answer 1 " << count / 2 << std::endl;
        }

        {   // Part 2
            int sum = 0;
            for(const auto& node : allNodes) {
               if (IsNodeInsideLoop(node, loopNodes)) {
                   sum++;
               }
            }
            std::cout << "Answer 2 " << sum << std::endl;
        }
    }

    void PopulateNodesMap() {
        nodes.clear();
        for (int y = 0; y < lines.size(); y++) {
            for (int x = 0; x < lines[y].size(); x++) {
                auto letter = lines[y][x];
                auto newNode = std::make_shared<Node>();
                newNode->nodeType = letter;
                newNode->y = y;
                newNode->x = x;
                nodes[y][x] = newNode;
                allNodes.push_back(newNode);
                PopulateNodeLinks(newNode);
            }
        }
    }

    void PopulateNodeLinks(const std::shared_ptr<Node>& thisNode) {
        bool supportUpwardsConnection = false;
        bool supportLeftConnection = false;
        switch (thisNode->nodeType) {
            case '-':
                supportLeftConnection = true;
                break;
            case '|':
                supportUpwardsConnection = true;
                break;
            case 'J':
                supportLeftConnection = true;
                supportUpwardsConnection = true;
                break;
            case 'L':
                supportUpwardsConnection = true;
                break;
            case 'F':
                break;
            case '7':
                supportLeftConnection = true;
                break;
            case 'S':
                supportLeftConnection = true;
                supportUpwardsConnection = true;
                startNode = thisNode;
                break;
            default:
                break;
        }

        if (supportUpwardsConnection) {
            auto nodeToConnect = GetValueIfExists(nodes, thisNode->y - 1, thisNode->x);
            if (nodeToConnect != nullptr) {
                switch (nodeToConnect->nodeType) {
                    case '|':
                    case 'S':
                    case '7':
                    case 'F':
                        ConnectNodes(thisNode, nodeToConnect);
                        break;
                    default:
                        break;
                }
            }
        }

        if (supportLeftConnection) {
            auto nodeToConnect = GetValueIfExists(nodes, thisNode->y, thisNode->x - 1);
            if (nodeToConnect != nullptr) {
                switch (nodeToConnect->nodeType) {
                    case '-':
                    case 'F':
                    case 'L':
                    case 'S':
                        ConnectNodes(thisNode, nodeToConnect);
                        break;
                    default:
                        break;
                }
            }
        }
    }

    static void ConnectNodes(const std::shared_ptr<Node>& n1, const std::shared_ptr<Node>& n2) {
        if (n1 == nullptr || n2 == nullptr) return;
        if (n2->pipeTo == nullptr) {
            n2->pipeTo = n1;
        } else {
            n2->pipeFrom = n1;
        }
        if (n1->pipeFrom == nullptr) {
            n1->pipeFrom = n2;
        } else {
            n1->pipeTo = n2;
        }
    }

    static std::shared_ptr<Node> GetValueIfExists(const Nodes& map,
                                                 const int& y, const int& x) {
        if (x < 0 || y < 0) {
            return nullptr;
        }
        auto it = map.find(y);
        if (it != map.end()) {
            const auto& innerMap = it->second;
            const auto innerIt = innerMap.find(x);
            if (innerIt != innerMap.end()) {
                return innerIt->second;
            }
        }
        return nullptr;
    }

    static bool IsNodeInsideLoop(const std::shared_ptr<Node>& point, const std::vector<std::shared_ptr<Node>>& loop) {
        if (point->isPartOfLoop) {
            return false;
        }
        bool result = false;
        int n = loop.size();
        for (int i = 0, j = n - 1; i < n; j = i++) {
            if (((loop[i]->y > point->y) != (loop[j]->y > point->y)) &&
                (point->x < (loop[j]->x - loop[i]->x) * (point->y - loop[i]->y) / (loop[j]->y - loop[i]->y) + loop[i]->x))
                result = !result;
        }
        return result;
    }
};
