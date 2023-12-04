#include "day01/day01.hpp"
#include "day02/day02.hpp"
#include "day03/day03.hpp"
#include "day04/day04.hpp"
#include "day05/day05.hpp"
#include <chrono>

int main() {
    auto t1 = std::chrono::high_resolution_clock::now();

    Day01 day01;
    Day02 day02;
    Day03 day03;
    Day04 day04;
    Day05 day05;

    auto t2 = std::chrono::high_resolution_clock::now();
    auto ms_int = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);
    std::cout << "Execution time " << ms_int.count() << "ms\n";
}