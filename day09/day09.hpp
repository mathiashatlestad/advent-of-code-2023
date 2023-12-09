#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include "../utilities.hpp"
#include <regex>

class Day09 {
public:
    Day09() {
        std::string name = "day09";
        std::cout << name << std::endl;
        Utilities::ReadFile(name + "/input.txt", lines);
        Solve();
    }
private:
    std::vector<std::string> lines;

    typedef std::vector<std::vector<long long>> Sequence;

    void Solve() {

        {  // Part 1
            long long sum = 0;
            for (auto & line : lines) {
                auto numbers = ParseLine(line);
                PopulateSequence(numbers);
                PopulateNewHistoryForSequencePt1(numbers);
                sum += numbers.front().back();
            }

            std::cout << "Answer 1 " << sum << std::endl;
        }

        {  // Part 2
            long long sum = 0;
            for (auto & line : lines) {
                auto numbers = ParseLine(line);
                PopulateSequence(numbers);
                PopulatePrevHistoryForSequencePt2(numbers);
                sum += numbers.front().front();
            }
            std::cout << "Answer 2 " << sum << std::endl;
        }
    }

    static Sequence ParseLine(const std::string& line) {
        std::stringstream ss(line);
        std::vector<long long> numbers;
        long long number;
        while (ss >> number) {
            numbers.push_back(number);
        }
        Sequence sec;
        sec.push_back(numbers);
        return sec;
    }

    static void PopulateSequence(Sequence& sec) {
        while (true) {
            auto last = sec.back();
            std::vector<long long> newLast;
            bool allAreZeroes = true;
            for (size_t i = 0; i < last.size() - 1; i++) {
                auto diff = last[i+1] - last[i];
                newLast.push_back(diff);
                if (diff != 0) allAreZeroes = false;
            }
            sec.push_back(newLast);
            if (allAreZeroes) break;
        }
    }

    static void PopulateNewHistoryForSequencePt1(Sequence& sec) {
        sec.back().push_back(0);
        for (int i = sec.size() - 2; i >= 0; i--) {
            auto lastInSec = sec[i].back();
            auto diff = sec[i+1].back();
            sec[i].push_back(lastInSec+diff);
        }
    }

    static void PopulatePrevHistoryForSequencePt2(Sequence& sec) {
        sec.back().insert(sec.back().begin(), 0);
        for (int i = sec.size() - 2; i >= 0; i--) {
            auto firstInList = sec[i].front();
            auto diff = sec[i+1].front();
            sec[i].insert(sec[i].begin(), firstInList-diff);
        }
    }
};
