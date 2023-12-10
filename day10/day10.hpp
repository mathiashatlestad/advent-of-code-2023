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
        bool isInsideLoop = false;
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
        for (int i = 0; i < lines.size(); i++) {
            for (int j = 0; j < lines[i].size(); j++) {
                auto letter = lines[i][j];
                auto newNode = std::make_shared<Node>();
                newNode->nodeType = letter;
                newNode->y = j;
                newNode->x = i;
                nodes[i][j] = newNode;
                allNodes.push_back(newNode);
                PopulateNodeLinks(i, j, newNode);
            }
        }
    }

    void PopulateNodeLinks(int i, int j, const std::shared_ptr<Node>& thisNode) {
        bool findAbove = false;
        bool findLeft = false;
        switch (thisNode->nodeType) {
            case '-':
                findLeft = true;
                break;
            case '|':
                findAbove = true;
                break;
            case 'J':
                findLeft = true;
                findAbove = true;
                break;
            case 'L':
                findAbove = true;
                break;
            case 'F':
                break;
            case '7':
                findLeft = true;
                break;
            case 'S':
                findLeft = true;
                findAbove = true;
                startNode = thisNode;
                break;
            default:
                break;
                // | is a vertical pipe connecting north and south.
                //- is a horizontal pipe connecting east and west.
                //L is a 90-degree bend connecting north and east.
                //J is a 90-degree bend connecting north and west.
                //7 is a 90-degree bend connecting south and west.
                //F is a 90-degree bend connecting south and east.
                //. is ground; there is no pipe in this tile.
                //S is the starting position of the animal; there is a pipe on this
        }

        if (findAbove) {
            auto nodeItAbove = GetValueIfExists(nodes, i - 1, j);
            if (nodeItAbove != nullptr) {
                bool shouldConnect = false;
                switch (nodeItAbove->nodeType) {
                    case '|':
                    case 'S':
                    case '7':
                    case 'F':
                        shouldConnect = true;
                        break;
                    default:
                        break;
                }
                if (shouldConnect) {
                    if (nodeItAbove->pipeTo == nullptr) {
                        nodeItAbove->pipeTo = thisNode;
                    } else {
                        nodeItAbove->pipeFrom = thisNode;
                    }
                    if (thisNode->pipeFrom == nullptr) {
                        thisNode->pipeFrom = nodeItAbove;
                    } else {
                        thisNode->pipeTo = nodeItAbove;
                    }
                }
            }
        }
        if (findLeft) {
            auto nodeItLeft = GetValueIfExists(nodes, i, j-1);
            if (nodeItLeft != nullptr) {
                bool shouldConnect = false;
                switch (nodeItLeft->nodeType) {
                    case '-':
                    case 'F':
                    case 'L':
                    case 'S':
                        shouldConnect = true;
                        break;
                    default:
                        break;
                }
                if (shouldConnect) {
                    if (nodeItLeft->pipeTo == nullptr) {
                        nodeItLeft->pipeTo = thisNode;
                    } else {
                        nodeItLeft->pipeFrom = thisNode;
                    }
                    if (thisNode->pipeFrom == nullptr) {
                        thisNode->pipeFrom = nodeItLeft;
                    } else {
                        thisNode->pipeTo = nodeItLeft;
                    }
                }
            }
        }
    }

    static std::shared_ptr<Node> GetValueIfExists(const Nodes& map,
                                                 const int& key1, const int& key2) {
        if (key1 < 0 || key2 < 0) {
            return nullptr;
        }
        auto it = map.find(key1);
        if (it != map.end()) {
            const auto& innerMap = it->second;
            const auto innerIt = innerMap.find(key2);
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
