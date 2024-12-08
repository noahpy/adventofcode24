
#include "../lib/parseutils.h"
#include "../lib/regexutils.h"
#include <iostream>
#include <map>

typedef std::map<char, std::vector<std::pair<int, int>>> Antennas;

void collectAntenna(Antennas& acc, std::vector<std::string> lines)
{
    for (size_t y = 0; y < lines.size(); ++y) {
        for (size_t x = 0; x < lines[y].size(); ++x) {
            if (lines[y][x] != '.') {
                acc[lines[y][x]].push_back({ x, y });
            }
        }
    }
}

size_t calculateAntiNodes(Antennas& acc, std::vector<std::string>& lines)
{
    size_t result = 0;
    std::map<std::pair<int, int>, bool> positionMap;
    for (auto& antenna : acc) {
        auto positions = antenna.second;
        // match two positions
        for (size_t i = 0; i < positions.size(); ++i) {
            for (size_t j = i + 1; j < positions.size(); ++j) {
                // calculate the two antinodes
                auto distancex = positions[i].first - positions[j].first;
                /* while (distancex % 2 == 0) { */
                /*     distancex /= 2; */
                /* } */
                auto distancey = positions[i].second - positions[j].second;
                /* while (distancey % 2 == 0) { */
                /*     distancey /= 2; */
                /* } */
                if(positionMap.find(positions[i]) == positionMap.end()) {
                    positionMap.insert_or_assign(positions[i], true);
                    ++result;
                }
                if(positionMap.find(positions[j]) == positionMap.end()) {
                    positionMap.insert_or_assign(positions[j], true);
                    ++result;
                }
                int ax = positions[i].first + distancex;
                int ay = positions[i].second + distancey;
                while (true) {
                    if (ax >= 0 && ax < lines[0].size() && ay >= 0 && ay < lines.size()) {
                        // check if unique
                        if (positionMap.find(std::make_pair(ax, ay)) == positionMap.end()) {
                            ++result;
                            positionMap.insert_or_assign(std::make_pair(ax, ay), true);
                            lines[ay][ax] = '#';
                        }
                    } else {
                        break;
                    }
                    ax += distancex;
                    ay += distancey;
                }
                auto bx = positions[j].first - distancex;
                auto by = positions[j].second - distancey;
                while (true) {
                    if (bx >= 0 && bx < lines[0].size() && by >= 0 && by < lines.size()) {
                        // check if unique
                        if (positionMap.find(std::make_pair(bx, by)) == positionMap.end()) {
                            ++result;
                            positionMap.insert_or_assign(std::make_pair(bx, by), true);
                            lines[by][bx] = '#';
                        }
                    }
                    else {
                        break;
                    }
                    bx -= distancex;
                    by -= distancey;
                }
            }
        }
    }
    return result;
}

int main(int argc, char* argv[])
{
    if (argc < 2) {
        std::cout << "Missing positional argument: input file" << std::endl;
        return 1;
    }
    auto lines = pautils::getLineVector(argv[1]);
    Antennas acc = {};
    collectAntenna(acc, lines);
    auto result = calculateAntiNodes(acc, lines);
    /* for (auto& line : lines) { */
    /*     std::cout << line << std::endl; */
    /* } */
    std::cout << result << std::endl;
}
