
#include "../lib/parseutils.h"
#include "../lib/regexutils.h"
#include <iostream>
#include <queue>
#include <vector>

#define MEMORY_SIZE 71
#define FALL_ITER 1024

struct Byte {
    int x;
    int y;
};

struct Point {
    int x;
    int y;
    int dist;
};

typedef size_t Acc;

typedef std::vector<Byte> Bytes;

class Compare {
public:
    bool operator()(const Point& a, const Point& b) const { return a.dist > b.dist; }
};

Bytes intializeBytes(std::vector<std::string> lines)
{
    Bytes bytes;
    for (auto s : lines) {
        auto matches = reutils::getMatches(s, "(\\d+)");
        Byte b;
        b.x = std::stoi(matches[0]);
        b.y = std::stoi(matches[1]);
        bytes.push_back(b);
    }
    return bytes;
}

void fallBytes(Bytes bytes, std::vector<std::string>& memory, int it)
{
    size_t index = 0;
    while (it) {
        Byte b = bytes.at(index);
        memory.at(b.y).at(b.x) = '#';
        --it;
        ++index;
    }
}

void runMaze(Acc& acc, std::vector<std::string>& memory)
{
    std::priority_queue<Point, std::vector<Point>, Compare> q;
    q.push({ 0, 0, 0 });
    while (!q.empty()) {
        auto [x, y, dist] = q.top();
        q.pop();
        if (x == MEMORY_SIZE - 1 && y == MEMORY_SIZE - 1) {
            acc = dist;
            return;
        }
        if (x + 1 < MEMORY_SIZE && memory.at(y).at(x + 1) == '.') {
            q.push({ x + 1, y, dist + 1 });
            memory.at(y).at(x + 1) = '#';
        }
        if (x - 1 >= 0 && memory.at(y).at(x - 1) == '.') {
            q.push({ x - 1, y, dist + 1 });
            memory.at(y).at(x - 1) = '#';
        }
        if (y + 1 < MEMORY_SIZE && memory.at(y + 1).at(x) == '.') {
            q.push({ x, y + 1, dist + 1 });
            memory.at(y + 1).at(x) = '#';
        }
        if (y - 1 >= 0 && memory.at(y - 1).at(x) == '.') {
            q.push({ x, y - 1, dist + 1 });
            memory.at(y - 1).at(x) = '#';
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
    Acc acc = 0;
    Bytes bytes = intializeBytes(lines);
    std::vector<std::string> memory;
    for (size_t i = 0; i < MEMORY_SIZE; ++i) {
        std::string s(MEMORY_SIZE, '.');
        memory.push_back(s);
    }
    fallBytes(bytes, memory, FALL_ITER);

    for (auto s: memory)
        std::cout << s << std::endl;

    runMaze(acc, memory);
    std::cout << acc << std::endl;
}
