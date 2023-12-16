#include <chrono>
#include "day01/day01.hpp"
#include "day02/day02.hpp"
#include "day03/day03.hpp"
#include "day04/day04.hpp"
#include "day05/day05.hpp"
#include "day06/day06.hpp"
#include "day07/day07.hpp"
#include "day08/day08.hpp"
#include "day09/day09.hpp"
#include "day10/day10.hpp"
#include "day11/day11.hpp"
#include "day12/day12.hpp"
#include "day13/day13.hpp"
#include "day14/day14.hpp"
#include "day15/day15.hpp"
#include "day16/day16.hpp"

int main() {
    auto t1 = std::chrono::high_resolution_clock::now();
/*'
Day01 day01;
 Day02 day02;
 Day03 day03;
 Day04 day04;
 Day05 day05;
 Day06 day06;
 Day07 day07;
 Day08 day08;
 Day09 day09;
 Day10 day10;
 Day11 day11;
 Day12 day12;
 Day13 day13;
 Day14 day14;
 Day15 day15;*/
    Day16 day16;
    auto t2 = std::chrono::high_resolution_clock::now();
    auto us_int = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1);
    std::cout << "Execution time " << us_int.count() / 1000.0 << "ms\n";
}