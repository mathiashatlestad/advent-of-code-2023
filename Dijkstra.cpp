#include "Dijkstra.h"

void Dijkstra::add_vertex(std::string name, const std::unordered_map<std::string, int>& edges)
{
    vertices.insert(std::unordered_map<std::string, const std::unordered_map<std::string, int>>::value_type(name, edges));
}

std::vector<std::string> Dijkstra::shortest_path(std::string start, std::string finish)
{
    std::unordered_map<std::string, int> distances;
    std::unordered_map<std::string, std::string> previous;
    std::vector<std::string> nodes;
    std::vector<std::string> path;

    auto comparator = [&] (std::string left, std::string right) { return distances[left] > distances[right]; };

    for (auto& vertex : vertices)
    {
        if (vertex.first == start)
        {
            distances[vertex.first] = 0;
        }
        else
        {
            distances[vertex.first] = std::numeric_limits<int>::max();
        }

        nodes.push_back(vertex.first);
        push_heap(begin(nodes), end(nodes), comparator);
    }

    while (!nodes.empty())
    {
        pop_heap(begin(nodes), end(nodes), comparator);
        std::string smallest = nodes.back();
        nodes.pop_back();

        if (smallest == finish)
        {
            while (previous.find(smallest) != end(previous))
            {
                path.push_back(smallest);
                smallest = previous[smallest];
            }

            break;
        }

        if (distances[smallest] == std::numeric_limits<int>::max())
        {
            break;
        }

        for (auto& neighbor : vertices[smallest])
        {
            int alt = distances[smallest] + neighbor.second;
            if (alt < distances[neighbor.first])
            {
                distances[neighbor.first] = alt;
                previous[neighbor.first] = smallest;
                make_heap(begin(nodes), end(nodes), comparator);
            }
        }
    }

    return path;
}