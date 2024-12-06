
#include "../lib/parseutils.h"
#include <iostream>
#include <map>

typedef size_t Acc;

int direction;
int posx, posy;
std::map<int, std::pair<int, int>> dir = {
    { 0, { 0, -1 } }, { 1, { 1, 0 } }, { 2, { 0, 1 } }, { 3, { -1, 0 } }
};

void f(Acc& acc, std::vector<std::string>& lines)
{
    std::cout << "Start: " << posx << " " << posy << std::endl;
    // step of guard
    while (posx >= 0 && posx < lines[0].size() && posy >= 0 && posy < lines.size()) {
        // step into direction or change direction
        auto nposx = posx + dir[direction].first;
        auto nposy = posy + dir[direction].second;
        if (nposx < 0 || nposx >= lines[0].size() || nposy < 0 || nposy >= lines.size()) {
            break;
        } else if (lines[nposy][nposx] == '#') {
            // change direction to right
            direction = (direction + 1) % 4;
            std::cout << "Changing direction!" << std::endl;
        } else {
            posx = nposx;
            posy = nposy;
            if (lines[posy][posx] != 'X') {
                acc++;
                lines[posy][posx] = 'X';
            }

            std::cout << posx << " " << posy << std::endl;
        }
        for (size_t i = 0; i < lines.size(); i++) {
            std::cout << lines[i] << std::endl;
        }
        std::cout << std::endl;
    }
}

int main(int argc, char* argv[])
{
    if (argc < 2) {
        std::cout << "Missing positional argument: input file" << std::endl;
        return 1;
    }
    auto lines = pautils::getLineVector(argv[1]);

    for (size_t i = 0; i < lines.size(); i++) {
        for (size_t j = 0; j < lines[i].size(); j++) {
            if (lines[i][j] == '^') {
                direction = 0;
                posx = j;
                posy = i;
            } else if (lines[i][j] == '>') {
                direction = 1;
                posx = j;
                posy = i;
            } else if (lines[i][j] == 'v') {
                direction = 2;
                posx = j;
                posy = i;
            } else if (lines[i][j] == '<') {
                direction = 3;
                posx = j;
                posy = i;
            }
        }
    }
    Acc acc = 1;
    lines[posy][posx] = 'X';
    f(acc, lines);
    std::cout << acc << std::endl;
}
