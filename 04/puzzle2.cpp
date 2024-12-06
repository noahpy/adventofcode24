
#include "../lib/parseutils.h"
#include <iostream>

typedef size_t Acc;

void f(Acc& acc, std::vector<std::string> lines)
{
    for (size_t x = 0; x < lines.size(); x++) {
        for (size_t y = 0; y < lines.size(); y++) {
            if (lines.at(x).at(y) == 'A') {
                // search for MS in diagonal directions
                if (x < 1 || y < 1 || x >= lines.size() - 1 || y >= lines.size() - 1) {
                    continue;
                }
                bool fdiagonal = false;
                if ((lines.at(x - 1).at(y - 1) == 'M' && lines.at(x + 1).at(y + 1) == 'S') ||
                    (lines.at(x - 1).at(y - 1) == 'S' && lines.at(x + 1).at(y + 1) == 'M')) {
                    fdiagonal = true;
                }
                bool sdiagonal = false;
                if ((lines.at(x - 1).at(y + 1) == 'M' && lines.at(x + 1).at(y - 1) == 'S') ||
                    (lines.at(x - 1).at(y + 1) == 'S' && lines.at(x + 1).at(y - 1) == 'M')) {
                    sdiagonal = true;
                }
                if (fdiagonal && sdiagonal) {
                    acc++;
                }
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
    auto lines = pautils::getLineVector(argv[1]);
    Acc acc = 0;
    f(acc, lines);
    std::cout << acc << std::endl;
}
