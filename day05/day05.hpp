#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include "../utilities.hpp"
#include <regex>

class Day05 {
public:
    Day05() {
        std::string name = "day05";
        std::cout << name << std::endl;
        Utilities::ReadFile(name + "/input.txt", lines);
        Solve();
    }
private:
    struct Range {
        long long destinationStart;
        long long destinationEnd;
        long long sourceStart;
        long long sourceEnd;
    };

    struct Mapping {
        std::vector<Range> ranges;
    };

    std::vector<std::string> lines;
    std::vector<std::shared_ptr<Mapping>> mappings;

    std::vector<long long> initialSeeds;

    int Solve() {

        mappings = ParseToMappings(lines);

        long long seedNumber;
        std::istringstream entryStream(lines[0].substr(6));
        while (entryStream >> seedNumber) {
            initialSeeds.push_back(seedNumber);
        }

        {  // Part 1
            long long lowestLocation = LONG_LONG_MAX;
            for (const auto& seed : initialSeeds) {
                long long currentLocation = seed;
                for (const auto& map : mappings) {
                   currentLocation = GetNextIndexFromRange(currentLocation, map->ranges);
                }
                if (currentLocation < lowestLocation) {
                    lowestLocation = currentLocation;
                }
            }

            std::cout << "Answer 1 " << lowestLocation << std::endl;
        }

        {  // Part 2
            long long foundLocation = 0;
            for (long long lowestLocation = 0; lowestLocation < LONG_LONG_MAX; ++lowestLocation) {
                long long seed = lowestLocation;
                for (const auto& map : std::views::reverse(mappings)) {
                    seed = GetReversedIndexFromRange(seed, map->ranges);
                }
                for (int i = 0; i < initialSeeds.size(); i+=2) {
                   if (seed >= initialSeeds[i] && seed <= initialSeeds[i] + initialSeeds[i+1]) {
                       foundLocation = lowestLocation;
                       break;
                   }
                }
                if (foundLocation > 0) {
                    break;
                }
            }
            std::cout << "Answer 2 " << foundLocation  << std::endl;
        }
        return 0;
    }

    static std::vector<std::shared_ptr<Mapping>> ParseToMappings(const std::vector<std::string>& input) {

        std::vector<std::shared_ptr<Mapping>> mappings;
        std::shared_ptr<Mapping> currentMapping = nullptr;
        for(auto const& line :  input) {
            if (line.contains("seeds:")) {
            } else if (line.contains("map")) {
                currentMapping = std::make_shared<Mapping>();
                mappings.push_back(currentMapping);
            } else if (!line.empty()) {
               Range range{};
               std::stringstream ss(line);
               ss >> range.destinationStart;
               ss >> range.sourceStart;
               int numbers;
               ss >> numbers;
               range.sourceEnd = range.sourceStart + numbers;
               range.destinationEnd = range.destinationStart + numbers;
               currentMapping->ranges.push_back(range);
            }
        }

        return mappings;
    }

    static long long GetNextIndexFromRange(long long i, const std::vector<Range>& ranges) {
        for (const auto& range : ranges) {
            if (i >= range.sourceStart && i <= range.sourceEnd) {
                return range.destinationStart + i - range.sourceStart;
            }
        }
        return i;
    };

    static long long GetReversedIndexFromRange(long long destination, const std::vector<Range>& ranges) {
        for (const auto& range : ranges) {
            if (destination >= range.destinationStart && destination <= range.destinationEnd) {
                return destination - range.destinationStart + range.sourceStart;
            }
        }
        return destination;
    };
};