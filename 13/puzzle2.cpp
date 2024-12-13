
#include "../lib/nutils.h"
#include "../lib/parseutils.h"
#include "../lib/printutils.h"
#include "../lib/regexutils.h"
#include <iostream>
#include <stdint.h>

typedef uint64_t Acc;

typedef std::pair<long long, long long> coord_t;

struct Arcade {
    coord_t diffA;
    coord_t diffB;
    coord_t prize;
};

std::vector<Arcade> initializeArcades(std::list<std::string> lines)
{
    std::vector<Arcade> arcades;
    while (!lines.empty()) {
        auto aLine = lines.front();
        lines.pop_front();
        auto bLine = lines.front();
        lines.pop_front();
        auto pLine = lines.front();
        lines.pop_front();
        if (lines.size()) {
            lines.pop_front();
        }

        // get the infos
        auto aMatches = reutils::getMatches(aLine, "(\\d+)");
        auto bMatches = reutils::getMatches(bLine, "(\\d+)");
        auto pMatches = reutils::getMatches(pLine, "(\\d+)");

        Arcade arcade;
        arcade.diffA.first = std::stol(aMatches[0]);
        arcade.diffA.second = std::stol(aMatches[1]);
        arcade.diffB.first = std::stol(bMatches[0]);
        arcade.diffB.second = std::stol(bMatches[1]);
        arcade.prize.first = std::stol(pMatches[0]) + 10000000000000;
        arcade.prize.second = std::stol(pMatches[1]) + 10000000000000;
        arcades.push_back(arcade);
    }
    return arcades;
}

void f(Acc& acc, Arcade ar)
{
    std::cout << "prize: " << ar.prize.first << " " << ar.prize.second << std::endl;
    int64_t m = ar.diffA.second * ar.prize.first - ar.diffA.first * ar.prize.second;
    int64_t k = ar.diffA.second * ar.diffB.first - ar.diffA.first * ar.diffB.second;
    if (nutils::modulo(m, k) != 0) {
        return;
    }
    auto b = m / k;
    auto a = (ar.prize.second - b * ar.diffB.second) / ar.diffA.second;
    std::cout << a << " " << b << std::endl;
    // sanity check
    if (a * ar.diffA.second + b * ar.diffB.second != ar.prize.second) {
        std::cout << a << " * " << ar.diffA.second << " + " << b << " * " << ar.diffB.second
                  << " != " << ar.prize.second << std::endl;
        return;
    }
    if (a * ar.diffA.first + b * ar.diffB.first != ar.prize.first) {
        std::cout << a << " * " << ar.diffA.first << " + " << b << " * " << ar.diffB.first
                  << " != " << ar.prize.first << std::endl;
        return;
    }
    acc += 3 * a + b;
}

int main(int argc, char* argv[])
{
    if (argc < 2) {
        std::cout << "Missing positional argument: input file" << std::endl;
        return 1;
    }
    auto lines = pautils::getLineList(argv[1]);
    auto arcades = initializeArcades(lines);
    Acc acc = 0;
    for (auto arc : arcades) {
        f(acc, arc);
    }
    std::cout << acc << std::endl;
}
