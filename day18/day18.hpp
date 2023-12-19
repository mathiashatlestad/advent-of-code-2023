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
            long long minMapI = 0;
            long long maxMapI = 0;
            long long minMapJ = 0;
            long long maxMapJ = 0;
            long long ans = 0;
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
                        incJ = 1*st.steps;;
                        break;
                }
                lastI += incI;
                lastJ += incJ;
                minMapI = std::min(minMapI, lastI);
                maxMapI = std::max(maxMapI, lastI);
                minMapJ = std::min(minMapJ, lastJ);
                maxMapJ = std::max(maxMapJ, lastJ);
                ring.push_back(Item {lastI, lastJ, st.color});
            }

            for (int i = minMapI; i <= maxMapI; i++) {
                for (int j = minMapJ; j <= maxMapJ; j++) {
                    if (IsNodeInsideLoop(i, j, ring)) {
                        ans++;
                    }
                }
            }
            std::cout << "Answer 1: " << ans << std::endl;
        }

        {  // Part 2
            ring.clear();
            long long minMapI = 0;
            long long maxMapI = 0;
            long long minMapJ = 0;
            long long maxMapJ = 0;
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
                minMapI = std::min(minMapI, lastI);
                maxMapI = std::max(maxMapI, lastI);
                minMapJ = std::min(minMapJ, lastJ);
                maxMapJ = std::max(maxMapJ, lastJ);
                ring.push_back(Item {lastI, lastJ, st.color});
            }

            for (int i = minMapI; i <= maxMapI; i++) {
                for (int j = minMapJ; j <= maxMapJ; j++) {
                    if (IsNodeInsideLoop(i, j, ring)) {
                        ans++;
                    }
                }
            }
            std::cout << "Answer 2: " << ans << std::endl;
        }
    }

    static bool IsNodeInsideLoop(int x, int y, const std::vector<Item>& loop) {
        bool result = false;
        int n = loop.size();
        for (int i = 0, j = n - 1; i < n; j = i++) {
            if ((y == loop[i].y && y == loop[j].y && x >= std::min(loop[i].x, loop[j].x) && x <= std::max(loop[i].x, loop[j].x)) ||
                (x == loop[i].x && x == loop[j].x && y >= std::min(loop[i].y, loop[j].y) && y <= std::max(loop[i].y, loop[j].y))) {
                return true;
            }

            if (((loop[i].y > y) != (loop[j].y > y)) &&
                (x < (loop[j].x - loop[i].x) * (y - loop[i].y) / (loop[j].y - loop[i].y) + loop[i].x))
                result = !result;
        }
        return result;
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
};
