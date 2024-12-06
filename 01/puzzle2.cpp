
#include "../lib/parseutils.h"
#include <algorithm>
#include <iostream>

typedef std::pair<std::vector<int>, std::vector<int>> Acc;

void f(Acc& acc, std::string line) {
    int first = std::stoi(line.substr(0, line.find(' ')));
    int second = std::stoi(line.substr(line.find(' ') + 1));
    acc.first.push_back(first);
    acc.second.push_back(second);
}

size_t calcDistances(Acc& acc) {
    std::sort(acc.first.begin(), acc.first.end());
    std::sort(acc.second.begin(), acc.second.end());

    auto& left = acc.first;
    auto& right = acc.second;
    

    size_t sum = 0;
    size_t left_index = 0;
    size_t right_index = 0;

    while (left_index < acc.first.size() && right_index < acc.second.size()) {
        if (left[left_index] < right[right_index]) {
            left_index++;
        }
        if (left[left_index] > right[right_index]) {
            right_index++;
        }
        if (left[left_index] == right[right_index]) {
            sum += left[left_index];
            right_index++;
        }
    }
    return sum;
}

int main(int argc, char* argv[])
{
    if (argc < 2) {
        std::cout << "Missing positional argument: input file" << std::endl;
        return 1;
    }
    std::list<std::string> lines = pautils::getLineList(argv[1]);
    Acc acc = std::make_pair(std::vector<int>(), std::vector<int>());
    pautils::runSingleLines<Acc>(acc, f, lines);

    auto result = calcDistances(acc);
    std::cout << result << std::endl;
}
