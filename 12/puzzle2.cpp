
#include "../lib/parseutils.h"
#include <algorithm>
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

size_t determineSides(std::vector<Coord> region, const std::vector<std::string>& lines)
{
    std::cout << "Region: " << lines.at(region.at(0).second).at(region.at(0).first) << std::endl;
    size_t result = 0;
    // find starting point
    std::map<Coord, std::vector<Coord>> directionalSides;
    for (auto plot : region) {
        for (auto dir : directions) {
            Coord neighbour = { plot.first + dir.first, plot.second + dir.second };
            if (neighbour.first < 0 || neighbour.first >= lines[0].length()) {
                if (directionalSides.find(dir) == directionalSides.end()) {
                    directionalSides.insert_or_assign(dir, std::vector<Coord>({ plot }));
                } else {
                    directionalSides.at(dir).push_back(plot);
                }
                continue;
            }
            if (neighbour.second < 0 || neighbour.second >= lines.size()) {
                if (directionalSides.find(dir) == directionalSides.end()) {
                    directionalSides.insert_or_assign(dir, std::vector<Coord>({ plot }));
                } else {
                    directionalSides.at(dir).push_back(plot);
                }
                continue;
            }
            if (lines.at(neighbour.second).at(neighbour.first) !=
                lines.at(plot.second).at(plot.first)) {
                if (directionalSides.find(dir) == directionalSides.end()) {
                    directionalSides.insert_or_assign(dir, std::vector<Coord>({ plot }));
                } else {
                    directionalSides.at(dir).push_back(plot);
                }
            }
        }
    }

    for (auto a : directionalSides) {
        std::map<int, std::vector<Coord>> heightToBool;
        auto plots = a.second;
        auto direction = a.first;
        std::cout << "For direction : " << direction.first << "," << direction.second << std::endl;
        std::function<int(Coord)> getHeight = [](Coord coord) { return coord.first; };
        std::function<int(Coord)> getNotHeight = [](Coord coord) { return coord.second; };
        if (direction.first == 0) {
            getHeight = [](Coord coord) { return coord.second; };
            getNotHeight = [](Coord coord) { return coord.first; };
        }
        for (auto plot : plots) {
            auto height = getHeight(plot);
            if (heightToBool.find(height) == heightToBool.end()) {
                heightToBool.insert_or_assign(height, std::vector<Coord>({ plot }));
            } else {
                heightToBool.at(height).push_back(plot);
            }
        }
        for (auto hPlots : heightToBool) {
            auto plots = hPlots.second;
            std::sort(plots.begin(), plots.end(), [getNotHeight](Coord a, Coord b) {
                return getNotHeight(a) < getNotHeight(b);
            });
            std::cout << "    For height " << hPlots.first << " we have ";
            for (auto plot : plots) {
                std::cout << plot.first << "," << plot.second << " ";
            }
            std::cout << std::endl;

            // check if continuous
            size_t breakCount = 0;
            size_t x = getNotHeight(plots.at(0));
            for (size_t i = 1; i < plots.size(); ++i) {
                if (getNotHeight(plots.at(i)) - x > 1) {
                    breakCount++;
                }
                x = getNotHeight(plots.at(i));
            }
            result += breakCount + 1;
            std::cout << "        Sides for this height: " << breakCount + 1 << std::endl;
        }
    }

    return result;
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
        auto sides = determineSides(region.second, lines);
        std::cout << "RESULT: For region "
                  << lines.at(region.second.at(0).second).at(region.second.at(0).first)
                  << " we have ";
        std::cout << area << " " << sides << std::endl;
        acc += area * sides;
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
