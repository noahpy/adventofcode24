
#include "../lib/parseutils.h"
#include "../lib/printutils.h"
#include "../lib/regexutils.h"
#include <iostream>

typedef size_t Acc;

typedef std::vector<std::string> Towels;
typedef std::vector<std::pair<std::string, std::string>> Overlaps;
typedef std::vector<std::string> Designs;

std::map<std::string, int> searchCache;
std::map<std::string, Acc> resultCache;

Acc recursiveDFS(Towels& towelList, std::string& design)
{
    if (design == "") {
        return 1;
    }
    if (resultCache.find(design) != resultCache.end()) {
        return resultCache.at(design);
    }
    Acc result = 0;
    // binary search with the first char
    std::string firstChar = design.substr(0, 1);
    size_t lower = 0;
    size_t upper = towelList.size() - 1;
    int point;
    if (searchCache.find(firstChar) != searchCache.end()) {
        point = searchCache.at(firstChar);
    } else {
        while (true) {
            point = (lower + upper) / 2;

            auto diff = firstChar.compare(0, 1, towelList.at(point));
            if (diff > 0) {
                lower = point + 1;
            } else if (diff < 0) {
                upper = point - 1;
            } else {
                break;
            }
            if (upper < lower) {
                break;
            }
        }
        searchCache.insert_or_assign(firstChar, point);
    }

    for (; point < towelList.size(); point++) {
        auto towel = towelList.at(point);
        auto diff = design.compare(0, towel.size(), towel);
        if (diff == 0) {
            auto sub = design.substr(towel.size());
            result += recursiveDFS(towelList, sub);
        }
        if(diff < 0) {
            break;
        }
    }
    resultCache.insert_or_assign(design, result);
    return result;
}

int main(int argc, char* argv[])
{
    if (argc < 2) {
        std::cout << "Missing positional argument: input file" << std::endl;
        return 1;
    }
    auto lines = pautils::getLineList(argv[1]);
    Acc acc = 0;

    Towels towelList = reutils::splitToVec(lines.front(), "(, )");
    lines.pop_front();
    lines.pop_front();
    Designs designList;
    for (auto line : lines) {
        designList.push_back(line);
    }

    std::sort(towelList.begin(), towelList.end());
    /* std::sort(designList.begin(), designList.end()); */

    /* prutils::printVector(towelList); */

    for (auto design : designList) {
        acc += recursiveDFS(towelList, design);
    }

    std::cout << acc << std::endl;
}
