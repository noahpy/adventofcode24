
#include "../lib/parseutils.h"
#include <iostream>
#include <map>

typedef size_t Acc;

typedef std::pair<int, int> Coord;

typedef std::map<Coord, size_t> RegionMap;

std::vector<Coord> directions = { { 0, 1 }, { 0, -1 }, { 1, 0 }, { -1, 0 } };

void traverseRegion(
    RegionMap& regionMap, const std::vector<std::string>& lines, Coord coord, size_t id)
{
    std::list<Coord> frontier = { coord };
    char regionChar = lines.at(coord.second).at(coord.first);

    while (!frontier.empty()) {
        Coord current = frontier.front();
        frontier.pop_front();
        for (auto direction : directions) {
            Coord next = { current.first + direction.first, current.second + direction.second };
            if (next.first < 0 || next.first >= lines[0].length()) {
                continue;
            }
            if (next.second < 0 || next.second >= lines.size()) {
                continue;
            }
            if (lines.at(next.second).at(next.first) == regionChar) {
                if (regionMap.find(next) == regionMap.end()) {
                    regionMap.insert_or_assign(next, id);
                    frontier.push_back(next);
                }
            }
        }
    }
}

void determineRegions(RegionMap& regionMap, const std::vector<std::string>& lines)
{
    size_t regionID = 0;
    for (size_t y = 0; y < lines.size(); ++y) {
        for (size_t x = 0; x < lines[0].length(); ++x) {
            if (regionMap.find({ x, y }) == regionMap.end()) {
                regionMap.insert_or_assign(std::make_pair<int, int>(x, y), regionID);
                traverseRegion(regionMap, lines, { x, y }, regionID);
                ++regionID;
            }
        }
    }
}

void calcCosts(Acc& acc, RegionMap& regionMap, const std::vector<std::string>& lines)
{
    std::map<size_t, std::vector<Coord>> regions;
    for (auto a : regionMap) {
        if (regions.find(a.second) == regions.end()) {
            regions.insert_or_assign(a.second, std::vector<Coord>({ a.first }));
        } else {
            regions.at(a.second).push_back(a.first);
        }
    }
    for (auto region : regions) {
        auto area = region.second.size();
        auto perimeter = 0;
        for (auto plot : region.second) {
            for (auto direction : directions) {
                Coord neighbour = { plot.first + direction.first, plot.second + direction.second };
                if (neighbour.first < 0 || neighbour.first >= lines[0].length()) {
                    ++perimeter;
                    continue;
                }
                if (neighbour.second < 0 || neighbour.second >= lines.size()) {
                    ++perimeter;
                    continue;
                }
                if (lines.at(neighbour.second).at(neighbour.first) !=
                    lines.at(plot.second).at(plot.first)) {
                    ++perimeter;
                }
            }
        }
        std::cout << "For region " << region.first << ": ";
        std::cout << area << " " << perimeter << std::endl;
        acc += area * perimeter;
    }
}

int main(int argc, char* argv[])
{
    if (argc < 2) {
        std::cout << "Missing positional argument: input file" << std::endl;
        return 1;
    }
    auto lines = pautils::getLineVector(argv[1]);
    RegionMap regionMap;
    determineRegions(regionMap, lines);
    Acc acc = 0;
    calcCosts(acc, regionMap, lines);
    std::cout << acc << std::endl;
}
