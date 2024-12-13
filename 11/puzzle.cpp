
#include "../lib/parseutils.h"
#include "../lib/regexutils.h"
#include <iostream>

typedef size_t Acc;

typedef std::pair<size_t, std::string> Stone;

// maps stones with their remaining amount of blinks to the final number of stones
std::map<Stone, size_t> stoneMap;

std::list<Stone> initStones(std::string line, size_t blink = 25)
{
    auto matches = reutils::getMatchesList(line, "(\\d+)");
    std::list<Stone> stones;
    for (auto match : matches) {
        Stone stone = { blink, match };
        stones.push_back(stone);
    }
    return stones;
}

size_t blink(Stone stone)
{
    if (stone.first == 0) {
        return 1;
    }
    if (stoneMap.find(stone) != stoneMap.end()) {
        return stoneMap.at(stone);
    }
    if (stone.second == "0") {
        Stone nextStone = { stone.first - 1, "1" };
        if (stoneMap.find(nextStone) == stoneMap.end()) {
            auto result = blink(nextStone);
            stoneMap.insert_or_assign(stone, result);
            return result;
        }
        return stoneMap.at(nextStone);
    } else if (stone.second.length() % 2 == 0) {
        Stone nextStone1 = { stone.first - 1, stone.second.substr(0, stone.second.length() / 2) };
        auto str = std::to_string(std::stol(stone.second.substr(stone.second.length() / 2)));
        Stone nextStone2 = { stone.first - 1, str };
        size_t stone1Result, stone2Result;
        if (stoneMap.find(nextStone1) == stoneMap.end()) {
            stone1Result = blink(nextStone1);
        } else {
            stone1Result = stoneMap.at(nextStone1);
        }
        if (stoneMap.find(nextStone2) == stoneMap.end()) {
            stone2Result = blink(nextStone2);
        } else {
            stone2Result = stoneMap.at(nextStone2);
        }
        auto result = stone1Result + stone2Result;
        stoneMap.insert_or_assign(stone, result);
        return result;
    } else {
        auto str = std::to_string(std::stol(stone.second) * 2024);
        Stone nextStone = { stone.first - 1, str };
        if (stoneMap.find(nextStone) == stoneMap.end()) {
            auto result = blink(nextStone);
            stoneMap.insert_or_assign(stone, result);
            return result;
        }
        return stoneMap.at(nextStone);
    }
}

void blinkSoManyTimes(Acc& acc, std::list<Stone> stones)
{
    while (!stones.empty()) {
        acc += blink(stones.front());
        stones.pop_front();
    }
}

int main(int argc, char* argv[])
{
    if (argc < 2) {
        std::cout << "Missing positional argument: input file" << std::endl;
        return 1;
    }
    auto blink = 25;
    if (argc == 3){
        blink = std::stol(argv[2]);
    }
    auto lines = pautils::getLineList(argv[1]);
    auto stones = initStones(lines.front(), blink);
    Acc acc = 0;
    blinkSoManyTimes(acc, stones);
    std::cout << acc << std::endl;
}
