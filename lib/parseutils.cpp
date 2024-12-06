
#include <fstream>
#include <functional>
#include <list>
#include <string>
#include <vector>

using namespace std;

namespace pautils {

auto getLineVector(string path) -> vector<string>
{
    ifstream file(path);
    string line;
    vector<string> result;
    while (getline(file, line)) {
        result.push_back(line);
    }
    return result;
}

auto getLineList(string path) -> list<string>
{
    ifstream file(path);
    string line;
    list<string> result;
    while (getline(file, line)) {
        result.push_back(line);
    }
    return result;
}

void runLines(
    function<void(list<string>)> f,
    function<list<string>(list<string>&)> getNextLines,
    list<string> lines)
{
    list<string> nextLines;
    while (!lines.empty()) {
        nextLines = getNextLines(lines);
        f(nextLines);
    }
}

void runSingleLines(
    function<void(string)> f, function<string(list<string>&)> getNextLine, list<string> lines)
{
    string nextLine = getNextLine(lines);
    while (!lines.empty()) {
        nextLine = getNextLine(lines);
        f(nextLine);
    }
}

auto getNextLine(list<string>& lines) -> string
{
    string s = lines.front();
    lines.pop_front();
    return s;
}

auto getNextLinePrePost(list<string>& lines) -> list<string>
{
    list<string> result;
    size_t n = 3;
    auto end = next(lines.begin(), min(n, lines.size()));
    copy(lines.begin(), end, back_inserter(result));
    lines.pop_front();
    if (lines.size() == 2) {
        lines.pop_front();
        lines.pop_front();
    }
    return result;
}

}
