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
        Utilities::ReadFile("day04/input.txt", lines);
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
            for (const auto& card : cards ) {
               sum += FindFactorForPart1(card);
            }
            std::cout << "Answer 1 " << sum << std::endl;
        }

        {  // Part 2
            for (auto& card : cards ) {
                PopulateCountsForPart2(card, cards);
            }
            int sum = 0;
            for (const auto& card : cards ) {
                sum += card.count;
            }
            std::cout << "Answer 2 " << sum << std::endl;
        }
        return 0;
    }
    struct Card {
        int id{};
        int count = 0;
        std::vector<int> winningNumbers;
        std::vector<int> myNumbers;
    };

    std::unordered_map<int, int> _matchesForCard;

    static Card ParseToCard(const std::string& input) {
        Card game;
        size_t colonPos = input.find(':');
        std::string gameID = input.substr(4, colonPos);
        game.id = stoi(gameID);
        
        std::stringstream ss(input.substr(colonPos + 2));
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

        return game;
    }

    void PopulateCountsForPart2(Card& card, std::vector<Card>& cards) {
        card.count++;
        int numMatches = _matchesForCard.find(card.id)->second;

        for (int i = card.id; i < card.id + numMatches; i++) {
            PopulateCountsForPart2(cards.at(i), cards);
        }
    }

    int FindFactorForPart1(const Card& card) {
        auto numMatches = std::ranges::count_if(card.myNumbers.begin(), card.myNumbers.end(), [&](int i) {
            return std::find(card.winningNumbers.begin(), card.winningNumbers.end(), i) != card.winningNumbers.end();
        });

        _matchesForCard.insert(std::make_pair(card.id, numMatches));

        if (numMatches == 0) {
            return 0;
        }

        return pow(2, (double) numMatches - 1);
    }
};