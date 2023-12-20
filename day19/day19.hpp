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

class Day19 {
public:
    Day19() {
        std::string name = "day19";
        std::cout << name << std::endl;
        Utilities::ReadFile(name + "/input.txt", lines);
        Solve();
    }

private:

    std::vector<std::string> lines;

    enum Operator {
        LessThan,
        GreaterThan,
        NoCheck
    };

    enum Type {
        X, M, A, S, FAlTY
    };

    struct Step {
        Type variable;
        int number;
        Operator checkType;
        std::string target;
    };

    struct Workflow {
        std::string name;
        std::vector<Step> steps;
    };

    struct Part
    {
       int X;
       int M;
       int A;
       int S;
    };

    std::unordered_map<std::string, std::shared_ptr<Workflow>> workflows;
    std::vector<std::shared_ptr<Part>> parts;
    std::shared_ptr<Workflow> firstFlow = nullptr;

    long long Rejects = 0;
    long long Accepted = 0;

    void Solve() {

        for (auto& line : lines){
            if (line.starts_with("{")) {
                parts.push_back(std::make_shared<Part>(parseToPart(line)));
            } else if (!line.empty()) {
                auto workflow = parseToWorkFlow(line);
                workflows[workflow->name] = workflow;
            }
        }

        workflows["A"] = std::make_shared<Workflow>(Workflow{"A"});
        workflows["R"] = std::make_shared<Workflow>(Workflow{"R"});

        {  // Part 1
            for (const auto& part : parts) {
                std::cout << "Pt" << part->X;
                HandlePart(part, workflows.find("in")->second);
                std::cout << std::endl;
            }
            std::cout << "Answer 1: " << Accepted << std::endl;
        }

        {  // Part 2
            int ans = 0;
            std::cout << "Answer 2: " << ans << std::endl;
        }
    }

    Part parseToPart(const std::string& line) {
        auto vars = Utilities::Split(line.substr(1, line.size() - 2), ',');
        Part pt;
        pt.X = stoi(vars[0].substr(2));
        pt.M = stoi(vars[1].substr(2));
        pt.A = stoi(vars[2].substr(2));
        pt.S = stoi(vars[3].substr(2));
        return pt;
    };

    std::shared_ptr<Workflow> parseToWorkFlow(const std::string& line) {
        auto wf = std::make_shared<Workflow>();
        wf->name = line.substr(0, line.find('{'));

        auto rest =  line.substr(line.find('{') + 1);
        auto list = Utilities::Split(rest.substr(0, rest.size() - 1), ',');
        for (auto& step : list) {
            Step sp;
            if (step.contains('<')) {
                sp.checkType = LessThan;
                sp.number = stoi(step.substr(step.find('<') + 1, step.size() - 2));
            }
            else if (step.contains('>')){
                sp.checkType = GreaterThan;
                sp.number = stoi(step.substr(step.find('>') + 1, step.size() - 2));
            }
            else {
                sp.checkType = NoCheck;
                sp.number = 0;
            }

            if (step.starts_with('x')) sp.variable = X;
            else if (step.starts_with('m')) sp.variable = M;
            else if (step.starts_with('a')) sp.variable = A;
            else if (step.starts_with('s')) sp.variable = S;
            else sp.variable = FAlTY;

            if (step.contains(':'))
                sp.target = step.substr(step.find(':') + 1, step.size()-1);
            else
                sp.target = step;

            wf->steps.push_back(sp);
        }

        return wf;
    };

    void HandlePart(const std::shared_ptr<Part>& part, const std::shared_ptr<Workflow>& wf) {
        std::cout << " -> " << wf->name;
        if (wf->name.starts_with("R")) {
            auto tot = (part->X + part->A + part->M + part->S);
            Rejects += tot;
            return;
        }
        if (wf->name.starts_with("A")){
            auto tot = (part->X + part->A + part->M + part->S);
            Accepted += tot;
            return;
        }
        for (const auto& step : wf->steps) {
            if (step.checkType == NoCheck) {
                return HandlePart(part, workflows.find(step.target)->second);
            }
            else if (step.checkType == GreaterThan) {
                switch (step.variable) {
                    case X:
                        if (part->X > step.number)
                            return HandlePart(part, workflows.find(step.target)->second);
                        break;
                    case M:
                        if (part->M > step.number)
                            return HandlePart(part, workflows.find(step.target)->second);
                        break;
                    case A:
                        if (part->A > step.number)
                            return HandlePart(part, workflows.find(step.target)->second);
                        break;
                    case S:
                        if (part->S > step.number )
                            return HandlePart(part, workflows.find(step.target)->second);
                        break;
                    default:
                        break;
                }
            }
            else if (step.checkType == LessThan) {
                switch (step.variable) {
                    case X:
                        if (part->X < step.number)
                            return HandlePart(part, workflows.find(step.target)->second);
                        break;
                    case M:
                        if (part->M < step.number)
                            return HandlePart(part, workflows.find(step.target)->second);
                        break;
                    case A:
                        if (part->A < step.number)
                            return HandlePart(part, workflows.find(step.target)->second);
                        break;
                    case S:
                        if (part->S < step.number)
                            return HandlePart(part, workflows.find(step.target)->second);
                        break;
                    default:
                        break;
                }
            }
        }
        throw;
    }
};
