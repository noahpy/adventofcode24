
#include "../lib/parseutils.h"
#include <iostream>
#include <map>
#include <set>

typedef size_t Acc;
typedef std::pair<int, int> Coord;
typedef std::map<Coord, int> ScoreMap;
typedef std::pair<Coord, int> CoordHeight;
std::vector<Coord> directions = { { 0, 1 }, { 0, -1 }, { 1, 0 }, { -1, 0 } };


void justCalc(Acc& acc, std::vector<std::string> lines)
{
    std::map<Coord, std::set<Coord>> results;
    std::map<Coord, std::set<Coord>> visited;
    for (int y = 0; y < lines.size(); y++) {
        for (int x = 0; x < lines[y].size(); x++) {
            Coord coord = { x, y };
            int height = lines[y][x] - '0';
            if (height == 0) {
                /* std::cout << "starting from " << coord.first << "," << coord.second << std::endl; */
                results.insert_or_assign(coord, std::set<Coord> {});
                visited.insert_or_assign(coord, std::set<Coord> {});
                std::list<CoordHeight> ways = { { coord, height } };
                while (!ways.empty()) {
                    CoordHeight way = ways.front();
                    auto currentCoord = way.first;
                    auto currentHeight = way.second;
                    /* std::cout << "poping " << currentCoord.first << "," << currentCoord.second */
                    /*           << std::endl; */
                    ways.pop_front();
                    for (auto& direction : directions) {
                        Coord nextCoord = { currentCoord.first + direction.first,
                                            currentCoord.second + direction.second };
                        if (nextCoord.first < 0 || nextCoord.first >= lines[0].size() ||
                            nextCoord.second < 0 || nextCoord.second >= lines.size()) {
                            continue;
                        }
                        if (visited.find(nextCoord) != visited.end()) {
                            continue;
                        }
                        int nextHeight = lines[nextCoord.second][nextCoord.first] - '0';
                        if (nextHeight - currentHeight == 1) {
                            if (nextHeight == 9) {
                                /* std::cout << "reached " << nextCoord.first << "," */
                                /*           << nextCoord.second << std::endl; */
                                results.at(coord).insert(nextCoord);
                            } else {
                                /* std::cout << "inserted " << nextCoord.first << "," */
                                /*           << nextCoord.second << std::endl; */
                                ways.push_back({ nextCoord, nextHeight });
                                visited.at(coord).insert(nextCoord);
                            }
                        }
                    }
                }
            }
        }
    }

    for (auto& result : results) {
        acc += result.second.size();
    }
}

int main(int argc, char* argv[])
{
    if (argc < 2) {
        std::cout << "Missing positional argument: input file" << std::endl;
        return 1;
    }
    ScoreMap scoreMap = {};
    auto lines = pautils::getLineVector(argv[1]);
    Acc acc = 0;
    justCalc(acc, lines);
    std::cout << acc << std::endl;
}
