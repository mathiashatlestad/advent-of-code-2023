#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include "../utilities.hpp"
#include <regex>

class DayXX {
    DayXX() {
        std::string name = "dayXX";
        std::cout << name << std::endl;
        Utilities::ReadFile(name + "/input.txt", lines);
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
