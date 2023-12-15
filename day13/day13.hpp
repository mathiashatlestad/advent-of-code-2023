#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <list>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <ranges>
#include <string_view>
#include "../utilities.hpp"

class Day13 {
public:
    Day13() {
        std::string name = "day13";
        std::cout << name << std::endl;
        Utilities::ReadFile(name + "/input.txt", lines);
        Solve();
    }
private:
    std::vector<std::string> lines;

    struct Pattern {
        std::vector<std::string> horizontal;
        int hOriginalLine = 0;
        int vOriginalLine = 0;
    };

    void Solve() {

        std::vector<Pattern> patterns;
        std::vector<std::string> currentLine;
        for (const auto& line : lines) {
            if (line.empty()) {
                patterns.push_back(GetPattern(currentLine));
                currentLine.clear();
                continue;
            }
            currentLine.push_back(line);
        }

        if (!currentLine.empty()) {
            patterns.push_back(GetPattern(currentLine));
        }

        {  // Part 1
            long long sum = 0;
            for (const auto& pattern : patterns) {
                sum += pattern.hOriginalLine*100;
                sum += pattern.vOriginalLine;
            }

            std::cout << "Answer 1 " << sum << std::endl;
        }

        {  // Part 2
            long long sum = 0;
            for (auto& pattern : patterns) {
                findDifferentPatternChanged(pattern);
                sum += pattern.hOriginalLine*100;
                sum += pattern.vOriginalLine;
            }
            if (sum == 24456) {
                std::cout << "Not RIGHT" << std::endl;
            }
            std::cout << "Answer 2 " << sum << std::endl;
        }
    };

    static bool isSymmetric(const std::vector<std::string>& vec, int left, int right) {
        while (left >= 0 && right <= vec.size() && vec[left] == vec[right]) {
            left--;
            right++;
        }
        return left < 0 || right == vec.size();
    }

    static int findReflection(const std::vector<std::string>& vec, int prevRef) {
        for (int i = 0; i < vec.size() - 1; i++) {
            if ((i+1) != prevRef && isSymmetric(vec, i, i+1) ) {
                return i + 1;
            }
        }
        return 0;
    }

    static bool FlippedMatches(const std::vector<std::string>& vec, int left, int right) {
        for (const auto& v : vec) {
            if (v[left] != v[right]) {
                return false;
            }
        }
        return true;
    }

    static int PrintRegular(const std::vector<std::string>& vec) {
        std::cout << "-----Regular----" << std::endl;
        for (const auto& s : vec) {
            std::cout << s << std::endl;
        }
        return 0;
    }


    static bool PrintFlipped(const std::vector<std::string>& vec) {
        std::cout << "-----Flipped----" << std::endl;
        for (int i = 0; i < vec[0].size(); i++) {
            for (const auto& s : vec) {
                std::cout << s[i];
            }
            std::cout << std::endl;
        }
        return true;
    }

    static bool isSymmetricFlipped(const std::vector<std::string>& vec, int left, int right) {
        while (left >= 0 && right < vec[0].size() && FlippedMatches(vec, left, right)) {
            left--;
            right++;
        }
        return left < 0 || right == vec[0].size();
    }

    static int findReflectionFlipped(const std::vector<std::string>& vec, int prevRef) {
        for (int i = 0; i < vec[0].size() - 1; i++) {
            if ((i+1) != prevRef && isSymmetricFlipped(vec, i, i+1)) {
                return i + 1;
            }
        }
        return 0;
    }

    static Pattern GetPattern(const std::vector<std::string>& input) {
        return Pattern{input, findReflection(input, -1),findReflectionFlipped(input, -1)};
    }

    static void findDifferentPatternChanged(Pattern& pattern) {
        for (int i = 0; i < pattern.horizontal.size(); i++) {
            for (int j = 0; j < pattern.horizontal[0].size(); j++) {
                pattern.horizontal[i][j] = (pattern.horizontal[i][j] == '#' ? '.' : '#');
                auto newHline = findReflection(pattern.horizontal, pattern.hOriginalLine);
                auto newVline = findReflectionFlipped(pattern.horizontal, pattern.vOriginalLine);
                pattern.horizontal[i][j] = (pattern.horizontal[i][j] == '#' ? '.' : '#');
                if (newHline == 0 && newVline == 0) continue;
                if ((newHline != 0 && newHline != pattern.hOriginalLine) || (newVline != 0 && newVline != pattern.vOriginalLine)) {
                    if (pattern.vOriginalLine == newVline){
                       pattern.vOriginalLine = 0;
                    } else {
                       pattern.vOriginalLine = newVline;
                    }
                    if (pattern.hOriginalLine == newHline) {
                        pattern.hOriginalLine = 0;
                    } else {
                        pattern.hOriginalLine = newHline;
                    }
                    return;
                }
            }
        }
        PrintRegular(pattern.horizontal);
        PrintFlipped(pattern.horizontal);
        throw;
    }
};
