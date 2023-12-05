#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include "../utilities.hpp"
#include <regex>
#include <math.h>

class Day05 {
public:
    Day05() {
        std::string name = "day05";
        std::cout << name << std::endl;
        Utilities::ReadFile(name + "/input.txt", lines);
        Solve();
    }
private:
    struct RangeMap {
        long long destinationStart;
        long long sourceStart;
        long long count;
    };

    struct Range {
        long long start;
        long long count;
    };

    struct Mapping {
        std::vector<RangeMap> ranges;
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
            std::vector<Range> seedRange;
            for (int i = 0; i < initialSeeds.size(); i+=2) {
                Range range{};
                range.start = initialSeeds[i];
                range.count = initialSeeds[i+1];
                seedRange.push_back(range);
            }
            long long foundLocation = LONG_LONG_MAX;
            auto ranges = CalculateAllPossibleRanges(seedRange);
            for (const auto& range : ranges) {
                if (range.start < foundLocation) {
                    foundLocation = range.start;
                }
            }
            std::cout << "Answer 2 " << foundLocation << std::endl;
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
               RangeMap range{};
               std::stringstream ss(line);
               ss >> range.destinationStart;
               ss >> range.sourceStart;
               ss >> range.count;
               currentMapping->ranges.push_back(range);
            }
        }

        return mappings;
    }

    static long long GetNextIndexFromRange(long long i, const std::vector<RangeMap>& ranges) {
        for (const auto& range : ranges) {
            if (i >= range.sourceStart && i <= range.sourceStart + range.count) {
                return range.destinationStart + i - range.sourceStart;
            }
        }
        return i;
    };

    static long long GetNextIndexFromRange(long long i, const RangeMap& range) {
        if (i >= range.sourceStart && i <= range.sourceStart + range.count) {
            return range.destinationStart + i - range.sourceStart;
        }
        return i;
    };

    std::vector<Range> CalculateAllPossibleRanges(const std::vector<Range>& seedRange) {
        std::vector<Range> possibleRanges;
        possibleRanges.insert(possibleRanges.end(), seedRange.begin(), seedRange.end());
        std::vector<Range> swap;
        for (auto& mapping : mappings) {
            swap.clear();
            for (auto& range : possibleRanges) {
                for (auto& newRange : CalculateNewRanges(range, mapping->ranges)) {
                    swap.push_back(newRange);
                }
            }
            possibleRanges.swap(swap);
        }
        return possibleRanges;
    }

    std::vector<Range> CalculateNewRanges(const Range& range, const std::vector<RangeMap>& mapping) {
        std::vector<Range> newRanges;

        long long currentStart = range.start;
        long long remainingCount = range.count;

        while (remainingCount > 0) {
            bool found = false;

            for (const auto& map : mapping) {
                if (currentStart >= map.sourceStart && currentStart < (map.sourceStart + map.count)) {

                    long long overlapEnd = std::min(currentStart + remainingCount, (map.sourceStart + map.count));
                    long long overlapCount = overlapEnd - currentStart;

                    newRanges.push_back({GetNextIndexFromRange(currentStart, map), overlapCount});

                    currentStart = overlapEnd;
                    remainingCount -= overlapCount;
                    found = true;
                    break;
                }
            }

            if (!found) {
                newRanges.push_back({currentStart, remainingCount});
                break;
            }
        }

        return newRanges;
    }
};