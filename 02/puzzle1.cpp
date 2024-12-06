
#include "../lib/parseutils.h"
#include "../lib/regexutils.h"
#include <iostream>

typedef size_t Acc;

void f(Acc& acc, std::string line)
{
    std::cout << line << std::endl;
    auto digits = reutils::getMatchesList(line, "(\\d+)");
    if (digits.size() < 2) {
        std::cout << "safe" << std::endl;
        ++acc;
        return;
    }
    auto first = std::stoi(digits.front());
    digits.pop_front();
    auto second = std::stoi(digits.front());
    digits.pop_front();

    int fac = 1;
    if (first > second) {
        fac = -1;
    }

    while (digits.size()) {
        auto diff = second - first;
        if (fac * diff < 1 || fac * diff > 3) {
            // not safe
            std::cout << "not safe" << std::endl;
            return;
        }
        first = second;
        second = std::stoi(digits.front());
        digits.pop_front();
    }
    auto diff = second - first;
    if (fac * diff < 1 || fac * diff > 3) {
        // not safe
        std::cout << "not safe" << std::endl;
        return;
    }
    std::cout << "safe" << std::endl;
    ++acc;
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
