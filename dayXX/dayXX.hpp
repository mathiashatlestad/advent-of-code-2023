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

class DayXX {
public:
    DayXX() {
        std::string name = "dayXX";
        std::cout << name << std::endl;
        Utilities::ReadFile(name + "/example.txt", lines);
        Solve();
    }
private:
    std::vector<std::string> lines;
    void Solve() {

        {  // Part 1
            std::cout << "Answer 1 " << "N/A" << std::endl;
        }

        {  // Part 2
            std::cout << "Answer 2 " << "N/A" << std::endl;
        }
    }

};
