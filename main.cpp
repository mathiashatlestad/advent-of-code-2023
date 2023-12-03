#include "day01/day01.hpp"
#include "day02/day02.hpp"
#include "day03/day03.hpp"
#include "day04/day04.hpp"
#include <chrono>

int main() {
    auto t1 = std::chrono::high_resolution_clock::now();

    std::cout << "Day1: " << std::endl;
    Day01::solve();
    std::cout << "Day2: " << std::endl;
    Day02::solve();
    std::cout << "Day3: " << std::endl;
    Day03::solve();
    std::cout << "Day4: " << std::endl;
    Day04::solve();

    auto t2 = std::chrono::high_resolution_clock::now();
    auto ms_int = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);
    std::cout << "Execution time " << ms_int.count() << "ms\n";
}