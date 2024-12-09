
#include "../lib/parseutils.h"
#include "../lib/printutils.h"
#include <iostream>
#include <map>
#include <utility>

typedef size_t Acc;

std::vector<std::string> calcDisk(
    std::string line, std::map<size_t, std::pair<size_t, size_t>>& sizePosMap, size_t& idMax)
{
    bool file = true;
    size_t id = 0;
    std::vector<std::string> ret;
    for (size_t i = 0; i < line.size(); i++) {
        size_t x = std::stoi(line.substr(i, 1));
        if (file) {
            size_t pos = ret.size();
            for (size_t j = 0; j < x; j++) {
                ret.push_back(std::to_string(id));
            }
            file = false;
            idMax = id;
            sizePosMap.insert_or_assign(id, std::make_pair(x, pos));
            id++;
        } else {
            for (size_t j = 0; j < x; j++) {
                ret.push_back(".");
            }
            file = true;
        }
    }
    return ret;
}

void rearrangeDisk(
    std::vector<std::string>& disk,
    std::map<size_t, std::pair<size_t, size_t>>& sizePosMap,
    size_t idMax)
{
    int id = idMax;
    while (id >= 0) {
        auto sizePos = sizePosMap.at(id);
        auto size = sizePos.first;
        auto pos = sizePos.second;
        bool consecutiveFree = false;
        size_t firstFree = 0;
        bool found = false;
        for (size_t i = 0; i < pos; i++) {
            if (disk.at(i) == ".") {
                if (!consecutiveFree) {
                    firstFree = i;
                }
                consecutiveFree = true;
                if (i - firstFree + 1 == size) {
                    found = true;
                    break;
                }
            } else {
                consecutiveFree = false;
            }
        }

        if (found) {
            for (size_t i = 0; i < size; i++) {
                disk.at(firstFree + i) = disk.at(pos + i);
            }
            for (size_t i = 0; i < size; i++) {
                disk.at(pos + i) = ".";
            }
        }
        --id;
    }
}

void f(Acc& acc, std::string line)
{
    std::map<size_t, std::pair<size_t, size_t>> sizePosMap;
    size_t idMax = 0;
    auto disk = calcDisk(line, sizePosMap, idMax);
    rearrangeDisk(disk, sizePosMap, idMax);
    /* prutils::printVector(disk); */
    // calculate checksum
    for (size_t i = 0; i < disk.size(); i++) {
        if (disk[i] != ".") {
            acc += i * std::stoi(disk[i]);
        }
    }
}

int main(int argc, char* argv[])
{
    if (argc < 2) {
        std::cout << "Missing positional argument: input file" << std::endl;
        return 1;
    }
    auto lines = pautils::getLineList(argv[1]);
    Acc acc = 0;
    pautils::runSingleLines<Acc>(acc, f, lines);
    std::cout << acc << std::endl;
}
