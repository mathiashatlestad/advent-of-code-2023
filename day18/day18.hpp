#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <unordered_set>
#include <list>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <ranges>
#include <string_view>
#include "../utilities.hpp"

class Day18 {
public:
    Day18() {
        std::string name = "day18";
        std::cout << name << std::endl;
        Utilities::ReadFile(name + "/input.txt", lines);
        Solve();
    }
private:
    enum Direction {
        Up, Down, Left, Right
    };

    struct Stage {
        Direction direction;
        long long steps;
        std::string color;
    };

    std::vector<Stage> stages;

    struct Item {
        long long x, y;
        std::string color;
    };

    std::vector<Item> ring;

    std::vector<std::string> lines;

    void Solve() {

        for (auto& line : lines) {
            auto split = Utilities::Split(line, ' ');
            Stage st;
            if (split[0] == "R") {
                st.direction = Right;
            } else if (split[0] == "L") {
                st.direction = Left;
            } else if (split[0] == "D") {
                st.direction = Down;
            } else if (split[0] == "U") {
                st.direction = Up;
            }
            st.steps = std::stoi(split[1]);
            st.color = split[2];
            stages.push_back(st);
        }

        {  // Part 1
            long long lastI = 0;
            long long lastJ = 0;
            for (auto& st : stages) {
                int incI = 0;
                int incJ = 0;
                switch (st.direction) {
                    case Up:
                        incI = -1*st.steps;
                        break;
                    case Down:
                        incI = 1*st.steps;;
                        break;
                    case Left:
                        incJ = -1*st.steps;
                        break;
                    case Right:
                        incJ = 1*st.steps;
                        break;
                }
                ring.push_back(Item {lastI, lastJ, st.color});
                lastI += incI;
                lastJ += incJ;
            }

            auto ans = polygonAreaWithEdges(ring);

            std::cout << "Answer 1: " << ans << std::endl;
        }

        {  // Part 2
            ring.clear();
            long long ans = 0;
            long long lastI = 0;
            long long lastJ = 0;
            for (auto& st : stages) {
                UpdateFromColor(st);
                long long incI = 0;
                long long incJ = 0;
                switch (st.direction) {
                    case Up:
                        incI = -1*st.steps;
                        break;
                    case Down:
                        incI = 1*st.steps;;
                        break;
                    case Left:
                        incJ = -1*st.steps;
                        break;
                    case Right:
                        incJ = 1*st.steps;;
                        break;
                }
                lastI += incI;
                lastJ += incJ;
                ring.push_back(Item {lastI, lastJ, st.color});
            }

            ans = polygonAreaWithEdges(ring);

            std::cout << "Answer 2: " << ans << std::endl;
        }
    }

    void UpdateFromColor(Stage& stage) {
        std::string steps = stage.color.substr(2,5);
        std::string dir = stage.color.substr(7, 1);
        if (dir == "0") {
            stage.direction = Right;
        } else if (dir == "1") {
            stage.direction = Down;
        } else if (dir == "2") {
            stage.direction = Left;
        } else if (dir == "3") {
            stage.direction = Up;
        }

        std::stringstream ss;
        ss << std::hex << steps;
        ss >> stage.steps;
    }

    long long polygonAreaWithEdges(const std::vector<Item>& points) {
        long long outerCount = 0.0;
        int n = points.size();

        for (size_t i = 0; i < points.size(); i++) {
            size_t j = (i + 1) % points.size();

            int dx = std::abs(points[j].x - points[i].x);
            int dy = std::abs(points[j].y - points[i].y);

            outerCount += (dx + dy);
        }

        long long area = 0;

        for (int i = 0; i < n; i++) {
            long j = (i + 1) % n;
            area += points[i].x * points[j].y;
            area -= points[j].x * points[i].y;
        }
        return outerCount / 2 + 1 + std::abs(area / 2);
    }
};
