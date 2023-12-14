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
        Utilities::ReadFile(name + "/example.txt", lines);
        Solve();
    }
private:
    std::vector<std::string> lines;

    struct Pattern {
        std::vector<std::string> horizontal;
        std::vector<std::string> vertical;
    };

    void Solve() {
        {  // Part 1
            long long sum = 0;
            std::vector<std::string> currentLines;
            for (const auto& line : lines) {
                if (line.empty()) {
                    auto pattern = GetPattern(currentLines);
                    sum += CalculateMirror(pattern.horizontal);
                    sum += CalculateMirror(pattern.vertical)*100;
                }
                currentLines.push_back(line);
            }

            std::cout << "Answer 1 " << sum << std::endl;
        }

        {  // Part 2
            std::cout << "Answer 2 " << "N/A" << std::endl;
        }
    };

    long long CalculateMirror(const std::vector<std::string>& data) {
        int maxMirror = 0;
        int maxMirrorAtIndex = 0;
        for (int i = 0; i < data.size(); i++) {
            for (int j = data.size() - 1; j > i; j--) {
                if (IsMirrored(data, i, j) && (j - i) > maxMirror) {
                    maxMirror = (j-i);
                    maxMirrorAtIndex = i;
                }
            }
        }
        return maxMirrorAtIndex;
    };

    static bool IsMirrored(const std::vector<std::string>& data, int i, int j) {
        while (i <= j) {
            if (data[i] != data[j])
                return false;
            i++;
            j--;
        }
        return true;
    };

    static Pattern GetPattern(const std::vector<std::string>& lines) {
        std::vector<std::string> allInI(lines.size());
        std::vector<std::string> allInJ(lines[0].size());
        for (int i= 0; i < lines.size(); i++) {
            for (int j = 0; j < lines[j].size(); j++) {
                allInI[i].push_back(lines[j][i]);
            }
        }

        for (int i= 0; i < lines[0].size(); i++) {
            for (int j = 0; j < lines.size(); j++) {
                allInJ[i].push_back(lines[i][j]);
            }
        }
        return Pattern{allInJ, allInI};
    }

};
