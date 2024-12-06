
#include "../lib/parseutils.h"
#include "../lib/stringutils.h"
#include "../lib/printutils.h"
#include "../lib/regexutils.h"
#include <iostream>
#include <map>

typedef size_t Acc;
std::map<int, std::vector<int>> precedenceMap = {};

void f(Acc& acc, std::string line) {
    auto matches = reutils::getMatches(line, "(\\d+)");
    bool correct = true;
    for (size_t i = 0; i < matches.size() && correct; i++) {
        auto x = std::stoi(matches.at(i));
        if (precedenceMap.find(x) == precedenceMap.end()) {
            continue;
        }
        auto rules = precedenceMap[x];
        for (auto r: rules){
            // search from beginning to i for r 
            for (size_t j = 0; j < i; j++){
                if (matches.at(j) == std::to_string(r)){
                    correct = false;
                    break;
                }
            }
        }
    }
    if (correct) {
    }
    else {
        // order them correctly
        std::vector<int> sorted = {};
        for (auto m: matches){
            auto x = std::stoi(m);
            if (precedenceMap.find(x) == precedenceMap.end()) {
                sorted.push_back(std::stoi(m));
                continue;
            }
            auto rules = precedenceMap.at(x);
            size_t i_max;
            if (sorted.size() == 0){
                i_max = 0;
            }
            else {
                i_max = sorted.size();
            }
            for (auto r: rules){
                for (size_t new_i = 0; new_i < sorted.size(); new_i++){
                    if (sorted.at(new_i) == r){
                        if (new_i < i_max){
                            i_max = new_i;
                        }
                    }
                }
            }
            sorted.insert(sorted.begin() + i_max, std::stoi(m));
        }
        prutils::printVector(sorted);
        acc += sorted.at(sorted.size() / 2);
    }
}

int main(int argc, char* argv[])
{
    if (argc < 2) {
        std::cout << "Missing positional argument: input file" << std::endl;
        return 1;
    }
    auto lines = pautils::getLineList(argv[1]);

    std::list<std::string> rules = {};
    while (lines.front() != "") {
        rules.push_back(lines.front());
        lines.pop_front();
    }
    lines.pop_front();

    for (auto rule : rules) {
        auto first = std::stoi(rule.substr(0, rule.find('|')));
        auto second = std::stoi(rule.substr(rule.find('|') + 1));
        if (precedenceMap.find(first) == precedenceMap.end()) {
            precedenceMap.insert_or_assign(first, std::vector<int>{second});
        }
        else {
            precedenceMap[first].push_back(second);
        }
    }

    /* for (auto p : precedenceMap){ */
    /*     std::cout << p.first << " = "; */
    /*     prutils::printVector(p.second); */
    /*     std::cout << std::endl; */
    /* } */

    Acc acc = 0;
    pautils::runSingleLines<Acc>(acc, f, lines);
    std::cout << acc << std::endl;
}
