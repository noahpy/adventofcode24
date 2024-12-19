
#include "../lib/parseutils.h"
#include "../lib/printutils.h"
#include "../lib/regexutils.h"
#include <iostream>

typedef size_t Acc;

typedef std::vector<std::string> Towels;
typedef std::vector<std::pair<std::string, std::string>> Overlaps;
typedef std::vector<std::string> Designs;

std::map<std::string, int> searchCache;

Overlaps findOverlapTowels(Towels& towelList, std::string& design)
{
    Overlaps overlapTowels;
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
        if (towel.at(0) != design.at(0)) {
            break;
        }
        if (design.substr(0, towel.size()) == towel) {
            overlapTowels.push_back({ towel, design.substr(towel.size()) });
        }
    }
    return overlapTowels;
}

void calcPossiblePatterns(Acc& acc, Towels& towelList, Designs& designList)
{
    for (auto design : designList) {
        /* std::cout << "design: " << design << std::endl; */
        Overlaps overlapTowels = { { "", design } };
        bool notFound = true;
        std::map<std::string, bool> visited;
        while (notFound) {
            Overlaps newOverlaps {};
            for (auto overlapTowel : overlapTowels) {
                auto remainingDesign = overlapTowel.second;
                if (visited.find(remainingDesign) != visited.end()) {
                    continue;
                }
                visited.insert_or_assign(remainingDesign, true);
                auto overlapList = findOverlapTowels(towelList, remainingDesign);
                newOverlaps.insert(newOverlaps.end(), overlapList.begin(), overlapList.end());
            }
            overlapTowels = newOverlaps;
            for (auto overlapTowel : overlapTowels) {
                if (overlapTowel.second == "") {
                    acc++;
                    notFound = false;
                    break;
                }
            }
            if (overlapTowels.empty()) {
                break;
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

    calcPossiblePatterns(acc, towelList, designList);

    std::cout << acc << std::endl;
}
