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
#include <queue>
#include "../utilities.hpp"

class Day20{
public:
    Day20() {
        std::string name = "day20";
        std::cout << name << std::endl;
        Utilities::ReadFile(name + "/input.txt", lines);
        Solve();
    }
private:

    struct SignalProcessor {
        std::string name;
        bool isInverter = false;
        bool isFlipFlop = false;
        bool flipFlopValue = false;
        std::vector<std::string> outputTargets;
        std::unordered_map<std::string, bool> inputValues;
    };

    struct Signal {
        bool isHigh = false;
        std::string target;
        std::string sender;
    };

    std::queue<Signal> signalQueue;

    std::unordered_map<std::string, std::shared_ptr<SignalProcessor>> signalProcessors;

    std::vector<std::string> lines;

    long long HighPulses = 0;
    long long LowPulses = 0;

    bool hitTheRxModule = false;

    void Solve() {

        for (auto& line : lines) {
            auto splitted = Utilities::Split(Utilities::Trim(line), '>');
            auto firstPart = splitted[0];
            auto listOfTargets = Utilities::Split(splitted[1], ',');
            SignalProcessor signalProcessor;
            if (firstPart.starts_with('%')) {
                signalProcessor.name = firstPart.substr(1, firstPart.size() - 3);
                signalProcessor.isInverter = false;
               signalProcessor.isFlipFlop = true;
            } else if (firstPart.starts_with('&')) {
                signalProcessor.name = firstPart.substr(1, firstPart.size() - 3);
                signalProcessor.isInverter = true;
                signalProcessor.isFlipFlop = false;
            } else {
                // Broadcaster
                signalProcessor.name = firstPart.substr(0, firstPart.size() - 2);
            }
            for (auto& tar : listOfTargets) {
                signalProcessor.outputTargets.push_back(Utilities::Trim(tar));
            }
            signalProcessors.insert(std::make_pair(signalProcessor.name, std::make_shared<SignalProcessor>(signalProcessor)));
        }

        for (auto& sig : signalProcessors) {
            if (sig.second->isInverter) {
                for (auto& sig2 : signalProcessors) {
                    if (sig2.first != sig.first &&
                            std::find(sig2.second->outputTargets.begin(), sig2.second->outputTargets.end(), sig.second->name) != sig2.second->outputTargets.end())
                        sig.second->inputValues.insert(std::make_pair(sig2.first, false));
                }
            }
        }

        {  // Part 1
            long long ans = 0;
            long long count = 0;
            for (long long i = 0; i < INT64_MAX; i++) {
                count++;
                Signal sig{};
                sig.isHigh = false;
                sig.sender = "button";
                sig.target = "broadcaster";
                signalQueue.push(sig);
                while (!signalQueue.empty()) {
                    auto& front = signalQueue.front();
                    HandleSignal(front);
                    signalQueue.pop();
                }
                if (hitTheRxModule) {
                    break;
                }
            }

            ans = HighPulses * LowPulses;
            std::cout << "Answer 1: " << count << std::endl;
        }

        {  // Part 2
            int ans = 0;
            std::cout << "Answer 2: " << ans << std::endl;
        }
    }

    void HandleSignal(const Signal& signal) {

        if (!signal.isHigh && signal.target == "rx") {
            hitTheRxModule = true;
        }

        if (signal.isHigh) {
            HighPulses++;
        } else {
            LowPulses++;
        }

        auto processorIt = signalProcessors.find(signal.target);
        if (processorIt == signalProcessors.end()) return;

        auto processor = processorIt->second;

        if (processor->isFlipFlop) {
            if (signal.isHigh)
                return;
            processor->flipFlopValue = !processor->flipFlopValue;
            for (const auto& tar : processor->outputTargets) {
                Signal newSig{};
                newSig.isHigh = processor->flipFlopValue;
                newSig.target = tar;
                newSig.sender = processor->name;
                signalQueue.push(newSig);
            }
            return;
        } else if (processor->isInverter) {
            processor->inputValues.find(signal.sender)->second = signal.isHigh;
            bool isHigh = true;
            for (auto& input : processor->inputValues) {
                if (!input.second) {
                    isHigh = false;
                    break;
                }
            }
            for (const auto& tar : processor->outputTargets) {
                Signal newSig{};
                newSig.isHigh = !isHigh;
                newSig.target = tar;
                newSig.sender = processor->name;
                signalQueue.push(newSig);
            }
            return;
        } else if (processor->name == "broadcaster") {
            for (const auto& tar : processor->outputTargets) {
                Signal newSig{};
                newSig.isHigh = false;
                newSig.target = tar;
                newSig.sender = processor->name;
                signalQueue.push(newSig);
            }
            return;
        }
        throw;
    }
};
