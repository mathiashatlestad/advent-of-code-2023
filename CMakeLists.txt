cmake_minimum_required(VERSION 3.26)
project(advent_of_code_2023)

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

set(CMAKE_CXX_STANDARD 23)

add_executable(advent_of_code_2023
        utilities.hpp
        utilities.cpp
        Dijkstra.cpp
        Dijkstra.h
        main.cpp
        day01/day01.hpp
        day02/day02.hpp
        day03/day03.hpp
        day04/day04.hpp
        day05/day05.hpp
        day06/day06.hpp
        day07/day07.hpp
        day08/day08.hpp
        day09/day09.hpp
        day10/day10.hpp
        day11/day11.hpp
        day12/day12.hpp
        day13/day13.hpp
)
