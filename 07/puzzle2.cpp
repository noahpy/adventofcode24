
#include "../lib/parseutils.h"
#include "../lib/printutils.h"
#include "../lib/regexutils.h"
#include <iostream>

typedef size_t Acc;

enum operation { ADD = 0, MUL = 1, CON = 2 };

std::string operationToString(operation op)
{
    if (op == ADD) {
        return "+";
    } else if (op == MUL) {
        return "*";
    } else if (op == CON) {
        return "||";
    }
    return "?";
}

bool incOpCombination(std::vector<operation>& ops)
{
    bool carry = true;
    for (size_t i = 0; i < ops.size() && carry; i++) {
        if (ops[i] == ADD) {
            ops[i] = MUL;
            carry = false;
        } else if (ops[i] == MUL) {
            ops[i] = CON;
            carry = false;
        } else if (ops[i] == CON) {
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

auto preProcessConcat(std::vector<operation> ops, std::vector<std::string> matches)
    -> std::pair<std::vector<operation>, std::vector<std::string>>
{
    // go through operations
    std::vector<operation> newOps;
    std::vector<std::string> newMatches = { matches[0] };
    for (size_t i = 0; i < ops.size(); i++) {
        if (ops[i] == CON) {
            newMatches.at(newMatches.size() - 1) += matches[i + 1];
        } else {
            newOps.push_back(ops[i]);
            newMatches.push_back(matches[i + 1]);
        }
    }
    return std::make_pair(newOps, newMatches);
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

    /* std::cout << "test: " << testValue << std::endl; */
    /* prutils::printVector(matches); */

    while (true) {
        /* prutils::printVector<operation>(ops, operationToString); */
        auto result = std::stol(matches[0]);
        for (size_t i = 1; i < matches.size(); i++) {
            if (ops[i - 1] == ADD) {
                result += std::stol(matches[i]);
            } else if (ops[i - 1] == MUL) {
                result *= std::stol(matches[i]);
            } else {
                result = std::stol(std::to_string(result) + matches[i]);
            }
        }
        /* std::cout << result << std::endl; */
        if (result == testValue) {
            /* std::cout << "found" << std::endl; */
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
