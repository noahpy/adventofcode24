
#include "../lib/parseutils.h"
#include "../lib/printutils.h"
#include "../lib/regexutils.h"
#include <iostream>

typedef size_t Acc;

void f(Acc& acc, std::string line)
{
    std::cout << line << std::endl;
    auto digits = reutils::getMatches(line, "(\\d+)");
    if (digits.size() < 2) {
        std::cout << "safe" << std::endl;
        ++acc;
        return;
    }

    auto first = std::stoi(digits.at(0));
    auto second = std::stoi(digits.at(1));

    int fac = 1;
    if (first > second) {
        fac = -1;
    }

    auto safe = true;

    auto index = 2;

    while (index < digits.size()) {
        auto diff = second - first;
        if (fac * diff < 1 || fac * diff > 3) {
            std::cout << "unsafe" << std::endl;
            safe = false;
            break;
        }
        first = second;
        second = std::stoi(digits.at(index++));
    }
    auto diff = second - first;
    if (fac * diff < 1 || fac * diff > 3) {
        std::cout << "unsafe" << std::endl;
        safe = false;
    }
    if (safe) {
        std::cout << "safe" << std::endl;
        ++acc;
        return;
    }

    for (size_t i = 0; i < digits.size(); ++i) {
        auto mod_digits = digits;
        mod_digits.erase(mod_digits.begin() + i);
        prutils::printVector(mod_digits);
        auto first = std::stoi(mod_digits.at(0));
        auto second = std::stoi(mod_digits.at(1));

        int fac = 1;
        if (first > second) {
            fac = -1;
        }

        auto safe = true;

        auto index = 2;

        while (index < mod_digits.size()) {
            auto diff = second - first;
            if (fac * diff < 1 || fac * diff > 3) {
                std::cout << "unsafe" << std::endl;
                safe = false;
                break;
            }
            first = second;
            second = std::stoi(mod_digits.at(index++));
        }
        auto diff = second - first;
        if (fac * diff < 1 || fac * diff > 3) {
            std::cout << "unsafe" << std::endl;
            safe = false;
        }
        if (safe) {
            std::cout << "safe" << std::endl;
            ++acc;
            return;
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
