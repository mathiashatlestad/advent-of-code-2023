#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#pragma once

class Utilities {
public:
    static bool ReadFile(const std::string& fileName, std::vector<std::string>& lines);
    static std::string Trim(const std::string& str);
};

