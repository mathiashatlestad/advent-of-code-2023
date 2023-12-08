#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include "../utilities.hpp"
#include <regex>

class Day08 {
public:
    Day08() {
        std::string name = "day08";
        std::cout << name << std::endl;
        Utilities::ReadFile(name + "/input.txt", lines);
        Solve();
    }
private:
    std::vector<std::string> lines;

    std::string instructions;

    struct Node {
        std::string id;
        std::shared_ptr<Node> left;
        std::shared_ptr<Node> right;
        std::vector<long long> zNodesCountBeforeReturnToItself;
    };

    std::unordered_map<std::string, std::shared_ptr<Node>> nodes;

    void Solve() {

        instructions = lines[0];

        for (size_t i = 2; i < lines.size(); i++) {
            std::stringstream  ss(lines[i]);
            std::shared_ptr<Node> node = std::make_shared<Node>();
            ss >> node->id;
            nodes.insert(std::make_pair(node->id, node));
        }

        for (size_t i = 2; i < lines.size(); i++) {
            ParseNodeLine(lines[i]);
        }

        /*
        {  // Part 1
            auto currentNode = nodes.find("AAA")->second;
            int count = 0;
            size_t instructionIt = 0;
            while (true) {
                if (instructions[instructionIt] == 'R') {
                    currentNode = currentNode->right;
                } else if (instructions[instructionIt] == 'L') {
                    currentNode = currentNode->left;
                }
                count++;
                instructionIt++;
                if (instructionIt >= instructions.size()) {
                    instructionIt = 0;
                }
                if (currentNode->id == "ZZZ") {
                    break;
                }
            }

            std::cout << "Answer 1 " << count << std::endl;
        }*/

        {  // Part 2
            std::vector<std::shared_ptr<Node>> relevantNodes;
            for (auto const& node : nodes) {
                if (node.first.ends_with('A')) {
                    relevantNodes.push_back(node.second);
                } else {
                    continue;
                }
                long long count = 0;
                size_t instructionIt = 0;
                auto nodeIt = node.second;
                while (true) {
                    if (instructions[instructionIt] == 'R') {
                        nodeIt = nodeIt->right;
                    } else if (instructions[instructionIt] == 'L') {
                        nodeIt = nodeIt->left;
                    }
                    count++;
                    instructionIt++;
                    if (nodeIt->id.ends_with('Z')) {
                        node.second->zNodesCountBeforeReturnToItself.push_back(count);
                    }
                    if (instructionIt >= instructions.size()) {
                        instructionIt = 0;
                    }
                    if (node.second == nodeIt) {
                        std::cout << "Answer 2 " << node.second->zNodesCountBeforeReturnToItself.size() << std::endl;
                        break;
                    }
                }
            }

            std::cout << "Answer 2 " << relevantNodes.size() << std::endl;
        }
    }

    void ParseNodeLine(const std::string& input) {
        std::istringstream iss(input);
        std::string firstNode, equalSign, secondNode, thirdNode;
        // Assuming the format is always "node = (node, node)"
        if (std::getline(iss, firstNode, ' ') &&
            std::getline(iss, equalSign, ' ') &&
            iss.get() && // Skip the '(' character
            std::getline(iss, secondNode, ',') &&
            iss.get() && // Skip the space after ','
            std::getline(iss, thirdNode, ')')) {

            // Trim potential extra spaces
            firstNode = Utilities::Trim(firstNode);
            secondNode = Utilities::Trim(secondNode);
            thirdNode = Utilities::Trim(thirdNode);

            auto firstNodeIt = nodes.find(firstNode);
            auto leftNodeIt = nodes.find(secondNode);
            auto rightNodeIt = nodes.find(thirdNode);
            firstNodeIt->second->left = leftNodeIt->second;
            firstNodeIt->second->right = rightNodeIt->second;

        } else {
            std::cout << "Invalid input format" << std::endl;
        }
    }
};
