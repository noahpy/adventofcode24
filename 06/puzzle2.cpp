
#include "../lib/parseutils.h"
#include <iostream>
#include <map>

typedef size_t Acc;

int startd;
int direction;
int startx, starty;
int posx, posy;
std::map<int, std::pair<int, int>> dir = {
    { 0, { 0, -1 } }, { 1, { 1, 0 } }, { 2, { 0, 1 } }, { 3, { -1, 0 } }
};

void f(Acc& acc, std::vector<std::string>& lines)
{
    for (size_t i = 0; i < lines.size(); i++) {
        for (size_t j = 0; j < lines[i].size(); j++) {
            posx = startx;
            posy = starty;
            direction = startd;
            std::vector<std::string> mlines = lines;
            mlines.at(i).at(j) = '#';
            std::map<std::tuple<int, int, int>, bool> mp;
            // step of guard
            while (posx >= 0 && posx < mlines[0].size() && posy >= 0 && posy < mlines.size()) {
                // step into direction or change direction
                auto nposx = posx + dir[direction].first;
                auto nposy = posy + dir[direction].second;
                if (nposx < 0 || nposx >= mlines[0].size() || nposy < 0 || nposy >= mlines.size()) {
                    break;
                } else if (mlines[nposy][nposx] == '#') {
                    // change direction to right
                    direction = (direction + 1) % 4;
                    if (mp.find(std::make_tuple(posx, posy, direction)) == mp.end()) {
                        mp.insert_or_assign(std::make_tuple(posx, posy, direction), true);
                    } else {
                        acc++;
                        break;
                    }
                } else {
                    posx = nposx;
                    posy = nposy;
                    if (mp.find(std::make_tuple(posx, posy, direction)) == mp.end()) {
                        mp.insert_or_assign(std::make_tuple(posx, posy, direction), true);
                    } else {
                        acc++;
                        break;
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
    startd = direction;
    startx = posx;
    starty = posy;
    Acc acc = 0;
    lines[posy][posx] = 'X';
    f(acc, lines);
    std::cout << acc << std::endl;
}
