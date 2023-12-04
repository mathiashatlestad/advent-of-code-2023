#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <sstream>
#include "../utilities.hpp"
#include <regex>
#include <ranges>

class Day02 {
public:
    Day02() {
        Utilities::ReadFile("day02/input.txt", lines);
        Solve();
    }
private:
    std::vector<std::string> lines;

    int Solve() {
        std::vector<Game> games;
        games.reserve(lines.size());
        for (const auto& line : lines)
            games.push_back(ParseToGame(line));

        {  // Part 1
            std::map<std::string, int> maxAllowed;
            maxAllowed.insert(std::make_pair("red", 12));
            maxAllowed.insert(std::make_pair("green", 13));
            maxAllowed.insert(std::make_pair("blue", 14));
            int sum = 0;
            auto relevantGames =
                    games
                    | std::views::filter([&](const Game& game) {return IsPossiblePart1(game, maxAllowed);})
                    | std::views::transform([](const Game& game){return game.id;});
            for (const auto& id : relevantGames) {
                sum += id;
            }
            std::cout << "Answer 1 " << sum << std::endl;
        }

        {  // Part 2
            int sum = 0;
            for (const auto& game : games)
                sum += PowerPart2(game);
            std::cout << "Answer 2 " << sum << std::endl;
        }
        return 0;
    }

    struct Cube {
        std::string color;
        int count{};
    };

    struct Game {
        int id{};
        std::vector<std::vector<Cube>> rounds;
    };

    static Game ParseToGame(const std::string& input) {
        Game game;
        size_t colonPos = input.find(':');
        std::string gameID = input.substr(4, colonPos);
        game.id = stoi(gameID);

        // Extracting the rounds
        std::string roundsPart = input.substr(colonPos + 2);  // skip the colon and space
        std::istringstream roundsStream(roundsPart);
        std::string round;

        while (std::getline(roundsStream, round, ';')) {
            std::istringstream roundStream(Utilities::Trim(round));
            std::string entry;
            std::vector<Cube> roundVector;
            while (std::getline(roundStream, entry, ',')) {
                std::istringstream entryStream(Utilities::Trim(entry));
                Cube newCube;
                entryStream >> newCube.count >> newCube.color;
                roundVector.push_back(newCube);
            }
            game.rounds.push_back(roundVector);
        }
        return game;
    }

     static bool IsPossiblePart1(const Game& game, const std::map<std::string, int>& maxAllowed) {
        for (const auto& round : game.rounds) {
            for (const auto& cube : round) {
                auto find = maxAllowed.find(cube.color);
                if (find == maxAllowed.end())
                    continue;
                if (find->second < cube.count) {
                    return false;
                }
            }
        }
        return true;
    }

    static int PowerPart2(const Game& game) {
        std::map<std::string, int> minMap;
        for (const auto& round2 : game.rounds) {
            for (const auto& cube : round2) {
                auto find = minMap.find(cube.color);
                if (find == minMap.end())
                    minMap.insert(std::make_pair(cube.color, cube.count));
                else if (find->second < cube.count)
                    find->second = cube.count;
            }
        }
        int factor = 1;
        for (const auto& min : minMap)
            factor = factor*min.second;
        return factor;
    }

};
