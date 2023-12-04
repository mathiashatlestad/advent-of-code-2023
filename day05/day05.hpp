#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include "../utilities.hpp"
#include <regex>

class Day05 {
public:
    Day05() {
        Utilities::ReadFile("day05/input.txt", lines);
        Solve();
    }
private:
    std::vector<std::string> lines;
    int Solve() {

        {  // Part 1
            std::cout << "Answer 1 " << "N/A" << std::endl;
        }

        {  // Part 2
            std::cout << "Answer 2 " << "N/A" << std::endl;
        }
        return 0;
    }
};
