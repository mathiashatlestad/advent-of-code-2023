#include "utilities.hpp"

bool Utilities::ReadFile(const std::string &fileName, std::vector<std::string> &lines) {
    std::ifstream in{fileName};
    if (!in) {
        std::cerr << "Cannot open file " << fileName << std::endl;
        return false;
    }
    std::string line;
    while (getline(in, line)) {
        lines.push_back(line);
    }
    in.close();

    return true;
}

// Function to trim spaces from a string
std::string Utilities::Trim(const std::string& str) {
    size_t first = str.find_first_not_of(' ');
    if (first == std::string::npos) return "";
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}
