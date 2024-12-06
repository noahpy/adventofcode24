#include <functional>
#include <list>
#include <string>

namespace pautils {

/**
 * Runs through every single line and call the given function f
 * on a single line and the accumulator sequentially.
 * Finally, returns the accumulator.
 *
 * * @param A: acc
 * @param function: f(A&, std::string) -> void
 * @param list<string>: lines
 *
 * @return A acc
 */
template <typename A>
A runSingleLines(A& acc, std::function<void(A&, std::string)> f, std::list<std::string> lines)
{
    for (std::string s : lines) {
        f(acc, s);
    }
    return acc;
}

/**
 * Runs through the lines by:
 * - retrieving the next line (a string) by calling getNextLine
 * - applies the function f on the accumulator (Type A) and the next line
 * After there are no lines left to run through, the final accumulator is
 * returned.
 *
 * @params:
 *  - A: acc
 *  - function: f(A&, string) -> void
 *  - function: getNextLine(list<string>&) -> string
 *  - list<string>: lines
 *
 *  @returns:
 *  - A: acc
 *   */
template <typename A>
A runSingleLines(
    A& acc,
    std::function<void(A&, std::string)> f,
    std::function<std::string(std::list<std::string>&)> getNextLine,
    std::list<std::string> lines)
{
    std::string nextLine;
    while (!lines.empty()) {
        nextLine = getNextLine(lines);
        f(acc, nextLine);
    }
    return acc;
}

/**
 * Runs through the lines by:
 * - retrieving the next lines (a list of strings) by calling getNextLine
 * - applies the function f on the accumulator (Type A) and the next lines
 * After there are no lines left to run through, the function
 * returns the accumulator.
 *
 * @params:
 *  - A: acc
 *  - function: f(A&, list<string>) -> void
 *  - function: getNextLine(list<string>&) -> list<string>
 *  - list<string>: lines
 *   */
template <typename A>
A runLines(
    A& acc,
    std::function<void(A&, std::list<std::string>)> f,
    std::function<std::list<std::string>(std::list<std::string>&)> getNextLines,
    std::list<std::string> lines)
{
    std::list<std::string> nextLines;
    while (!lines.empty()) {
        nextLines = getNextLines(lines);
        f(acc, nextLines);
    }
    return acc;
}

/**
 * Runs through the lines by:
 * - retrieving the next lines (a list of strings) by calling getNextLine
 * - applies the function f on the accumulator (Type A), the next lines and the current number of
 * line, starting at 0. After there are no lines left to run through, the function returns the
 * accumulator.
 *
 * @params:
 *  - A: acc
 *  - function: f(A&, list<string>, size_t) -> void
 *  - function: getNextLine(list<string>&) -> list<string>
 *  - list<string>: lines
 *   */
template <typename A>
A runLines(
    A& acc,
    std::function<void(A&, std::list<std::string>, size_t count)> f,
    std::function<std::list<std::string>(std::list<std::string>&)> getNextLines,
    std::list<std::string> lines)
{
    std::list<std::string> nextLines;
    size_t count = 0;
    while (!lines.empty()) {
        nextLines = getNextLines(lines);
        f(acc, nextLines, count);
        count++;
    }

    return acc;
}

/**
 * Runs through the lines by:
 * - retrieving the next lines (a list of strings) by calling getNextLine
 * - applies the function f on the next lines
 * After there are no lines left to run through, the function
 * returns.
 *
 * @params:
 *  - function: f(list<string>) -> void
 *  - function: getNextLine(list<string>&) -> list<string>
 *  - list<string>: lines
 *   */
void runLines(
    std::function<void(std::list<std::string>)> f,
    std::function<std::list<std::string>(std::list<std::string>&)> getNextLines,
    std::list<std::string> lines);

/**
 * Runs through the lines by:
 * - retrieving the next line (a string) by calling getNextLine
 * - applies the function f on the next line
 * After there are no lines left to run through, the function
 * returns.
 *
 * @params:
 *  - function: f(string) -> void
 *  - function: getNextLine(list<string>&) -> string
 *  - list<string>: lines
 *   */
void runSingleLines(
    std::function<void(std::string)> f,
    std::function<std::list<std::string>(std::list<std::string>&)> getNextLine,
    std::list<std::string> lines);

/**
 * Takes a path to a file as input and returns
 * a vector of the lines of the file read as a string.
 *
 * @param string path
 *
 * @return vector<string> result
 */
auto getLineVector(std::string path) -> std::vector<std::string>;

/**
 * Takes a path to a file as input and returns
 * a list of the lines of the file read as a string.
 *
 * @param string path
 *
 * @return list<string> result
 */
auto getLineList(std::string path) -> std::list<std::string>;

/**
 * Removes the first line from the line list and returns it
 *
 * @params:
 * - list<string>&: lines
 *
 * @returns:
 * - string: line
 */
auto getNextLine(std::list<std::string>& lines) -> std::string;

/**
 * Removes the first line from the line list and returns a list of the first,
 * second and third line.
 *
 * @params:
 * - list<string>&: lines
 *
 * @returns:
 * - list<string>: line
 */
auto getNextLinePrePost(std::list<std::string>& lines) -> std::list<std::string>;

}
