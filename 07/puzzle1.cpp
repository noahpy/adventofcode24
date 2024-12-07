
#include "../lib/parseutils.h"
#include "../lib/regexutils.h"
#include <iostream>

typedef size_t Acc;

enum operation { ADD = 0, MUL = 1 };

bool incOpCombination(std::vector<operation>& ops)
{
    bool carry = true;
    for (size_t i = 0; i < ops.size() && carry; i++) {
        if (ops[i] == ADD) {
            ops[i] = MUL;
            carry = false;
        } else if (ops[i] == MUL) {
            ops[i] = ADD;
        }
    }
    return carry;
}

bool endOfCombinations(std::vector<operation>& ops)
{
    for (size_t i = 0; i < ops.size(); i++) {
        if (ops[i] == ADD) {
            return false;
        }
    }
    return true;
}

void f(Acc& acc, std::string line)
{
    auto testValue = std::stol(line.substr(0, line.find(':')));
    auto equation = line.substr(line.find(':') + 1, line.length());
    auto matches = reutils::getMatches(equation, "(\\d+)");
    std::vector<operation> ops;
    for (size_t i = 0; i < matches.size() - 1; i++) {
        ops.push_back(ADD);
    }

    if (matches.size() == 0) {
        return;
    }
    if (matches.size() == 1) {
        acc += std::stol(matches[0]) == testValue ? testValue : 0;
        return;
    }

    while (true) {
        auto result = std::stol(matches[0]);
        for (size_t i = 1; i < matches.size(); i++) {
            if (ops[i - 1] == ADD) {
                result += std::stol(matches[i]);
            } else if (ops[i - 1] == MUL) {
                result *= std::stol(matches[i]);
            }
        }
        if (result == testValue) {
            acc += testValue;
            return;
        } else {
            bool carry = incOpCombination(ops);
            if (carry) {
                return;
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
    auto lines = pautils::getLineList(argv[1]);
    Acc acc = 0;
    pautils::runSingleLines<Acc>(acc, f, lines);
    std::cout << acc << std::endl;
}
