
#include "../lib/parseutils.h"
#include <iostream>
#include <map>
#include <queue>

typedef size_t Acc;

typedef std::pair<int, int> Pos;

// position, direction, distance
typedef std::tuple<Pos, int, int> State;

class Compare {
public:
    bool operator()(const State& a, const State& b) const
    {
        return std::get<2>(a) > std::get<2>(b);
    }
};

std::vector<Pos> directions = { { 1, 0 }, { 0, 1 }, { -1, 0 }, { 0, -1 } };

std::pair<State, Pos> getInitialState(std::vector<std::string> lines)
{
    State start;
    Pos goal;
    for (int i = 0; i < lines.size(); i++) {
        for (int j = 0; j < lines[i].size(); j++) {
            if (lines[i][j] == 'S') {
                start = State { { i, j }, 1, 0 };
            }
            if (lines[i][j] == 'E') {
                goal = { i, j };
            }
        }
    }
    return std::make_pair(start, goal);
}

void runMaze(Acc& acc, std::vector<std::string> lines, State state, Pos goal)
{
    std::priority_queue<State, std::vector<State>, Compare> q;
    std::map<Pos, int> visited;
    visited.insert_or_assign(std::get<0>(state), 1);
    q.push(state);
    while (!q.empty()) {
        auto [cur_pos, cur_dir, cur_dist] = q.top();
        std::cout << cur_pos.first << "," << cur_pos.second << " " << cur_dir << " " << cur_dist
                  << std::endl;
        q.pop();
        if (cur_pos == goal) {
            acc = cur_dist;
            return;
        }
        visited.insert_or_assign(cur_pos, cur_dist);
        for (int i = 0; i <directions.size(); i++) {
            int x = cur_pos.first + directions.at(i).first;
            int y = cur_pos.second + directions.at(i).second;
            if (x < 0 || x >= lines.size() || y < 0 || y >= lines[0].size()) {
                continue;
            }
            if (lines[x][y] == '#') {
                continue;
            }
            if (visited.find({ x, y }) != visited.end()) {
                continue;
            }
            // no 180 degree turns allowed
            if (std::abs(i - cur_dir) == 2) {
                continue;
            }
            auto toNext = 1 + 1000 * ( i!= cur_dir);
            std::cout << "discovered " << x << "," << y << " " << i<< " with cost " << toNext
                      << std::endl;
            q.push({ { x, y }, i, cur_dist + toNext });
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
    auto [start, goal] = getInitialState(lines);
    Acc acc = 0;
    runMaze(acc, lines, start, goal);
    std::cout << acc << std::endl;
}
