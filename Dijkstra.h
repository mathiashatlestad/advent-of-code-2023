//
// Created by mathias.hatlestad@bidbax.no on 11/12/2023.
//

#ifndef ADVENT_OF_CODE_2023_DIJKSTRA_H
#define ADVENT_OF_CODE_2023_DIJKSTRA_H

#include <unordered_map>
#include <vector>
#include <limits>
#include <algorithm>
#include <iostream>

class Dijkstra {
    std::unordered_map<std::string, const std::unordered_map<std::string, int>> vertices;

public:
    void add_vertex(std::string name, const std::unordered_map<std::string, int>& edges);
    std::vector<std::string> shortest_path(std::string start, std::string finish);
};


#endif //ADVENT_OF_CODE_2023_DIJKSTRA_H
