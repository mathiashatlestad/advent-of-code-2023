#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <algorithm>
#include "../utilities.hpp"
#include <regex>

class Day06 {
public:
    Day06() {
        std::string name = "day06";
        std::cout << name << std::endl;
        Utilities::ReadFile(name + "/input.txt", lines);
        Solve();
    }
private:
    std::vector<std::string> lines;

    struct Race {
        long long recordTime;
        long long distance;
    };

    void Solve() {
        std::string timePart = lines[0].substr(lines[0].find(':') + 1);
        std::string distancePart = lines[1].substr(lines[1].find(':') + 1);

        {  // Part 1
            std::stringstream timeStream(timePart);
            std::stringstream distanceStream(distancePart);
            std::vector<Race> races;
            long long time;
            while (timeStream >> time) {
                Race race{};
                race.recordTime = time;
                distanceStream >> race.distance;
                races.push_back(race);
            }

            long long sum = 1;
            for (const auto& race : races) {
                sum *= NumberOfWaysForRace(race);
            }
            std::cout << "Answer 1 " << sum << std::endl;
        }

        {  // Part 2
            distancePart.erase(remove( distancePart.begin(), distancePart.end(), ' '), distancePart.end());
            timePart.erase(remove( timePart.begin(), timePart.end(), ' '), timePart.end());
            Race race{stoll(timePart), stoll(distancePart)};
            std::cout << "Answer 2 " << NumberOfWaysForRace(race) << std::endl;
        }
    }

    static long long NumberOfWaysForRace(const Race& race) {
        long long waysToWinTheRace = 0;
        long long minSpeedRequiredToBeatRecord = (race.distance / race.recordTime);
        for (long long timeSpendSpeedingUpBeforeLaunch = minSpeedRequiredToBeatRecord; timeSpendSpeedingUpBeforeLaunch <= race.recordTime; timeSpendSpeedingUpBeforeLaunch++) {
            long long myRaceDistanceInTheRecordTime = (race.recordTime - timeSpendSpeedingUpBeforeLaunch) * timeSpendSpeedingUpBeforeLaunch;
            if (myRaceDistanceInTheRecordTime > race.distance) {
                waysToWinTheRace++;
            } else if (waysToWinTheRace > 0) {
                break;
            }
        }
        return waysToWinTheRace;
    };
};
