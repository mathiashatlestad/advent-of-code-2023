#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include "../utilities.hpp"
#include <regex>
#include <ranges>
#include <string_view>
#include <cmath>
#include <unordered_map>

class Day04 {
public:
    Day04() {
        std::string name = "day04";
        std::cout << name << std::endl;
        Utilities::ReadFile(name + "/input.txt", lines);
        Solve();
    }
private:
    std::vector<std::string> lines;
    int Solve() {
        std::vector<Card> cards;
        cards.reserve(lines.size());
        for (auto& line : lines) {
            cards.push_back(ParseToCard(line));
        }

        {  // Part 1
            int sum = 0;
            for (const auto& card : cards) {
               sum += card.matches > 0 ? pow(2, card.matches - 1) : 0;
            }
            std::cout << "Answer 1 " << sum << std::endl;
        }

        {  // Part 2
            int sum = 0;
            for (int i = 0; i < cards.size(); i++) {
                for (int j = 0; j < cards[i].matches; j++) {
                    cards[i + 1 + j].count += cards[i].count;
                }
                sum += cards[i].count;
            }
            std::cout << "Answer 2 " << sum << std::endl;
        }
        return 0;
    }

    struct Card {
        int count = 1;
        long matches;
        std::vector<int> winningNumbers;
        std::vector<int> myNumbers;
    };

    static Card ParseToCard(const std::string& input) {
        Card game;
        std::stringstream ss(input.substr(input.find(':') + 2));
        int dlmCounter = 0;
        std::string tmp;
        while (std::getline(ss, tmp, '|')) {
            std::vector<int> innerVector;
            std::stringstream segmentStream(tmp);
            std::string number;

            while (segmentStream >> number) {
                innerVector.push_back(std::stoi(number));
                if (dlmCounter == 0) {
                    game.winningNumbers.push_back(std::stoi(number));
                } else if (dlmCounter == 1) {
                    game.myNumbers.push_back(std::stoi(number));
                }
            }
            dlmCounter++;
        }

        game.matches = std::ranges::count_if(game.myNumbers.begin(), game.myNumbers.end(), [&](int i) {
            return std::find(game.winningNumbers.begin(), game.winningNumbers.end(), i) != game.winningNumbers.end();
        });
        return game;
    }
};