#include <string>
#include <list>
#include <iostream>
#include <sstream>
#include "../utilities.hpp"
#include <regex>

class Day07 {
public:
    Day07() {
        std::string name = "day07";
        std::cout << name << std::endl;
        Utilities::ReadFile(name + "/input.txt", lines);
        Solve();
    }
private:
    std::vector<std::string> lines;
    enum HandType {
        FiveOfAKind = 0,
        FourOfAKind = 1,
        FullHouse = 2,
        ThreeOfAKind = 3,
        TwoPairs = 4,
        OnePair = 5,
        HighCard = 6
    };

    struct Hand {
        std::string hand;
        HandType type;
        int bet;
        std::vector<size_t> weights;
    };

    std::list<Hand> hands;

    void Solve() {
        for (auto const& line :  lines) {
            Hand hand{};
            std::stringstream ss(line);
            ss >> hand.hand;
            ss >> hand.bet;
            hands.push_back(hand);
        }

        {  // Part 1
            int rank = 1;
            int sum = 0;

            for (auto& hand :  hands) {
                hand.type = GetType(hand.hand, false);
                hand.weights = GetWeights(hand.hand, false);
            }

            hands.sort(SortFunc);

            for (auto const &hand: hands) {
                sum += hand.bet * rank;
                rank++;
            }

            std::cout << "Answer 1 " << sum << std::endl;
        }

        {  // Part 2
            for (auto& hand : hands) {
                hand.weights = GetWeights(hand.hand, true);
                hand.type = GetType(hand.hand, true);
            }

            int rank = 1;
            int sum = 0;

            hands.sort(SortFunc);

            for (auto const &hand: hands) {
                sum += hand.bet * rank;
                rank++;
            }

            std::cout << "Answer 2 " << sum << std::endl;
        }
    }

    static bool SortFunc(const Hand& hand1, const Hand& hand2) {

        if (hand1.type != hand2.type) {
            return hand1.type > hand2.type;
        }
        for (int i = 0; i < hand1.hand.size(); i++) {
            if (hand1.weights[i] == hand2.weights[i]) {
                continue;
            }
            return hand1.weights[i] > hand2.weights[i];
        }
        return false;
    }

    static std::vector<size_t> GetWeights(const std::string& hand, bool joker) {
        std::vector<size_t> weight;
        std::string order = joker ? "AKQT98765432J" : "AKQJT98765432";
        for (auto const &c: hand) {
            auto pos = order.find(c);
            weight.push_back(pos);
        }
        return weight;
    }

    static HandType GetType(const std::string& hand, bool joker) {
        std::unordered_map<char, int> cardCounts;
        int jokerCount = 0;

        for (char c : hand) {
            if (joker && c == 'J') {
                jokerCount++;
            } else {
                cardCounts[c]++;
            }
        }

        if (jokerCount == 5)
            return FiveOfAKind;

        if (jokerCount > 0) {
            char mostCommonCard = std::max_element(cardCounts.begin(), cardCounts.end(),
                                                   [](const auto& a, const auto& b) { return a.second < b.second; })->first;
            cardCounts[mostCommonCard] += jokerCount;
        }

        switch (cardCounts.size()) {
            case 1:
                return FiveOfAKind;
            case 2:
                for (const auto& [card, count] : cardCounts) {
                    if (count == 4)
                        return FourOfAKind;
                }
                return FullHouse;
            case 3:
                for (const auto& [card, count] : cardCounts) {
                    if (count == 3)
                        return ThreeOfAKind;
                }
                return TwoPairs;
            case 4:
                return OnePair;
            case 5:
                return HighCard;
            default:
                throw std::runtime_error("Invalid hand");
        }
    };
};
