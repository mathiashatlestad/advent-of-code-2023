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
    int Solve() {
        std::vector<std::string> lines;
        Utilities::ReadFile("day04/input.txt", lines);
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
private:
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

        // Extracting the rounds
        std::string cardsPart = input.substr(colonPos + 2);  // skip the colon and space
        std::stringstream ss(cardsPart);
        int delCounter = 0;

        while (std::getline(ss, cardsPart, '|')) {
            std::vector<int> innerVector;
            std::stringstream segmentStream(cardsPart);
            std::string number;

            while (segmentStream >> number) {
                innerVector.push_back(std::stoi(number));
                if (delCounter == 0) {
                    game.winningNumbers.push_back(std::stoi(number));
                } else {
                    game.myNumbers.push_back(std::stoi(number));
                }
            }
            delCounter++;
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