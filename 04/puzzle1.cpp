
#include "../lib/parseutils.h"
#include <iostream>

typedef size_t Acc;

std::vector<std::pair<int, int>> directions = { { 1, 0 },  { 1, -1 }, { 0, -1 }, { -1, -1 },
                                                { -1, 0 }, { -1, 1 }, { 0, 1 },  { 1, 1 } };

void f(Acc& acc, std::vector<std::string> lines)
{
    for (size_t x = 0; x < lines.size(); x++) {
        for (size_t y = 0; y < lines.size(); y++) {
            if (lines.at(x).at(y) == 'X') {
                // search for XMAS in all directions
                for (auto direction : directions) {
                    int px = x;
                    int py = y;
                    std::list<char> xmas = { 'M', 'A', 'S' };
                    while (xmas.size() > 0) {
                        px += direction.first;
                        py += direction.second;
                        if (px >= lines.size() || py >= lines.size() || px < 0 || py < 0) {
                            break;
                        }
                        if (lines.at(px).at(py) == xmas.front()) {
                            xmas.pop_front();
                        } else {
                            break;
                        }
                    }
                    if (xmas.size() == 0) {
                        acc++;
                    }
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
