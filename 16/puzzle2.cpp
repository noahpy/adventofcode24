
#include "../lib/parseutils.h"
#include <climits>
#include <iostream>
#include <map>
#include <queue>
#include <set>

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
    std::map<std::pair<Pos, int>, int> visited;
    std::map<std::pair<Pos, int>, std::vector<std::pair<Pos, int>>> came_from;
    int smallest = INT_MAX;
    q.push(state);
    while (!q.empty()) {
        auto [cur_pos, cur_dir, cur_dist] = q.top();
        std::cout << cur_pos.first << "," << cur_pos.second << " " << cur_dir << " " << cur_dist
                  << std::endl;
        q.pop();
        if (visited.find({ cur_pos, cur_dir }) != visited.end()) {
            continue;
        }
        visited.insert_or_assign({ cur_pos, cur_dir }, cur_dist);
        for (int i = 0; i < directions.size(); i++) {
            int x = cur_pos.first + directions.at(i).first;
            int y = cur_pos.second + directions.at(i).second;
            if (x < 0 || x >= lines.size() || y < 0 || y >= lines[0].size()) {
                continue;
            }
            if (lines[x][y] == '#') {
                continue;
            }
            // no 180 degree turns allowed
            if (std::abs(i - cur_dir) == 2) {
                continue;
            }
            auto toNext = 1 + 1000 * (i != cur_dir);
            std::cout << "discovered " << x << "," << y << " " << i << " with cost " << toNext
                      << std::endl;
            if (Pos { x, y } == goal) {
                if (cur_dist + toNext <= smallest) {
                    smallest = cur_dist + toNext;
                } else {
                    std::cout << "too big goal " << std::endl;
                    continue;
                }
            }

            if (visited.find({ { x, y }, i }) != visited.end()) {
                if (visited.at({ { x, y }, i }) < cur_dist + toNext) {
                    std::cout << "Skipping " << x << "," << y << " " << i << " with cost " << toNext
                              << std::endl;
                    continue;
                }
            }
            q.push({ { x, y }, i, cur_dist + toNext });
            if (came_from.find({ { x, y }, i }) == came_from.end()) {
                came_from.insert_or_assign(
                    { { x, y }, i }, std::vector<std::pair<Pos, int>> { { cur_pos, cur_dir } });
            } else {
                came_from.at({ { x, y }, i }).push_back({ cur_pos, cur_dir });
                std::cout << "pushing back" << std::endl;
            }
        }
    }

    std::set<Pos> seats;
    std::list<std::pair<Pos, int>> to_check = {};
    to_check.push_back(std::make_pair(goal, 0));
    to_check.push_back(std::make_pair(goal, 1));
    to_check.push_back(std::make_pair(goal, 2));
    to_check.push_back(std::make_pair(goal, 3));

    while (!to_check.empty()) {
        auto pos = to_check.front();
        std::cout << "at " << pos.first.first << "," << pos.first.second << " " << pos.second
                  << std::endl;
        lines[pos.first.first][pos.first.second] = 'O';
        to_check.pop_front();
        if (came_from.find(pos) == came_from.end()) {
            continue;
        }
        auto prevs = came_from.at(pos);
        for (auto prev : prevs) {
            if (seats.find(prev.first) == seats.end()) {
                std::cout << "found " << prev.first.first << "," << prev.first.second << std::endl;
                seats.insert(prev.first);
            }
            to_check.push_back(prev);
        }
    }

    for (auto line : lines)
        std::cout << line << std::endl;

    acc = seats.size() + 1;
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
