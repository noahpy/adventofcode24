
#include "../lib/parseutils.h"
#include "../lib/printutils.h"
#include <iostream>

typedef size_t Acc;

std::vector<std::string> calcDisk(std::string line)
{
    bool file = true;
    size_t id = 0;
    std::vector<std::string> ret;
    for (size_t i = 0; i < line.size(); i++) {
        auto x = std::stoi(line.substr(i, 1));
        if (file) {
            for (size_t j = 0; j < x; j++) {
                ret.push_back(std::to_string(id));
            }
            file = false;
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

void rearrangeDisk(std::vector<std::string>& disk)
{
    size_t emptyP = 0;
    size_t fileP = disk.size() - 1;

    while (emptyP < fileP) {
        if (disk[emptyP] == ".") {
            if (disk[fileP] != ".") {
                disk[emptyP] = disk[fileP];
                disk[fileP] = ".";
                emptyP++;
                fileP--;
            }
            else {
                fileP--;
            }
        } else {
            emptyP++;
        }
    }
}

void f(Acc& acc, std::string line)
{
    auto disk = calcDisk(line);
    rearrangeDisk(disk);
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
