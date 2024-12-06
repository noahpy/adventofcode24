
#include "../lib/parseutils.h"
#include "../lib/regexutils.h"
#include <iostream>

typedef size_t Acc;
bool enabled = true;

void f(Acc& acc, std::string line)
{
    auto matches = reutils::getMatchesList(line, "(mul\\(\\d+,\\d+\\)|do\\(\\)|don't\\(\\))");
    auto func = [](Acc& mul, std::string s) { 
        auto first = s.substr(0, s.find(','));
        auto second = s.substr(s.find(',') + 1, s.length());
        mul += stol(first) * stol(second);
        std::cout << first << " * " << second << " = " << stol(first) * stol(second) << std::endl;
    };
    for (auto match : matches) {
        std::cout << match << std::endl;
        if (match == "do()"){
            enabled = true;
        }
        if (match == "don't()"){
            enabled = false;
        }
        else {
            if (enabled){
                acc = reutils::runOnMatches<Acc>(acc, match, "(\\d+,\\d+)", func);
            }
        }
    }
}

int main(int argc, char* argv[])
{
    if (argc < 2) {
        std::cout << "Missing positional argument: input file" << std::endl;
        return 1;
    }
    std::list<std::string> lines = pautils::getLineList(argv[1]);
    Acc acc = 0;
    pautils::runSingleLines<Acc>(acc, f, lines);
    std::cout << acc << std::endl;
}
