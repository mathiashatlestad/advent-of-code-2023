#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <list>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <ranges>
#include <string_view>
#include "../utilities.hpp"

class Day15 {
public:
    Day15() {
        std::string name = "day15";
        std::cout << name << std::endl;
        Utilities::ReadFile(name + "/input.txt", lines);
        Solve();
    }
private:
    std::vector<std::string> lines;

    struct Lens {
        std::string label;
        int strength;
    };

    std::vector<std::list<std::shared_ptr<Lens>>> boxes;

    void Solve() {

        {  // Part 1
            int sum = 0;
            for (const auto& part : Utilities::Split(lines[0], ',')) {
                sum+=HashValue(part);
            }
            std::cout << "Answer 1 " << sum << std::endl;
        }

        for (int i = 0; i < 256; i++) {
            boxes.emplace_back();
        }

        {  // Part 2
            for (const auto& part : Utilities::Split(lines[0], ',')) {
                if (part.contains('-')) {
                    auto label = part.substr(0, part.find('-'));
                    auto boxNum = HashValue(label);
                    RemoveFromBox(label, boxNum);
                } else {
                    auto label = part.substr(0, part.find('='));
                    auto boxNum = HashValue(label);
                    int focal = stoi(part.substr(part.find('=')+1));
                    AddToBox(label, focal, boxNum);
                }
            }

            int sum = 0;
            for (int i = 0; i < boxes.size(); i++) {
                sum += CalculateBoxStrength(boxes[i], i);
            }

            std::cout << "Answer 2 " << sum << std::endl;
        }
    }

    static int HashValue(const std::string& str) {
        int current = 0;
        for (const auto& ch : str) {
            current += int(ch);
            current *= 17;
            current %= 256;
        }
        return current;
    }

    void AddToBox(const std::string& lensLabel, const int& lensStrength, const int& boxNumber) {
        auto& theBox = boxes[boxNumber];

        auto match = std::find_if(theBox.cbegin(), theBox.cend(), [&] (const std::shared_ptr<Lens>& s) {
            return s->label == lensLabel;
        });

        if (match != theBox.end()) {
            match->get()->label = lensLabel;
            match->get()->strength = lensStrength;
        } else {
            auto newLens = std::make_shared<Lens>();
            newLens->label = lensLabel;
            newLens->strength = lensStrength;
            theBox.push_back(newLens);
        }
    };

    void RemoveFromBox(const std::string& lensLabel, const int& boxNumber) {
        boxes[boxNumber].remove_if([&] (const std::shared_ptr<Lens>& s) {
            return s->label == lensLabel;});
    };

    static int CalculateBoxStrength(const std::list<std::shared_ptr<Lens>>& box, const int& boxNum) {
        int i = 1;
        int sum = 0;
        for (const auto& lens : box) {
            sum += (boxNum + 1) * lens->strength * i;
            i++;
        }
        return sum;
    }

    void PrintBoxes() {
        for (int i = 0; i < boxes.size(); i++) {
            if (boxes[i].empty()) continue;
            std::cout << "Box " << i << ": ";
            for (const auto& lens : boxes[i]) {
                std::cout << " [" << lens->label << " " << lens->strength << "] ";
            }
            std::cout << std::endl;
        }
    }
};
