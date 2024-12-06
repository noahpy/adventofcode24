
#include <list>
#include <optional>
#include <regex>

namespace reutils {

/**
 * Calls function f on every regex match found on the given string,
 * with the respective accumulator.
 *
 * @params:
 * - A: acc
 * - string: s
 * - string: regex_pattern
 * - function: f(A&, string) -> void
 *
 * @returns:
 * - A: acc
 */
template <typename A>
auto runOnMatches(A acc, std::string s, std::string pattern, std::function<void(A&, std::string)> f)
    -> A
{
    std::regex rpattern(pattern);
    std::sregex_iterator it(s.begin(), s.end(), rpattern);
    std::sregex_iterator end;

    while (it != end) {
        f(acc, it->str(1));
        ++it;
    }

    return acc;
}

/**
 * Returns the first match found on a given regex pattern in a
 * given string. Returns a optional containing the string if there
 * was one found.
 *
 * @params:
 *  - string: s
 *  - string: pattern
 *
 *  @returns:
 *  - string: result
 */
auto getMatch(std::string s, std::string pattern) -> std::optional<std::string>;

/**
 * Returns every match found on a given regex pattern in a
 * given string in a vector.
 *
 * @params:
 *  - string: s
 *  - string: pattern
 *
 *  @returns:
 *  - vector<string> result
 */
auto getMatches(std::string s, std::string pattern) -> std::vector<std::string>;


/**
 * Returns every match found on a given regex pattern in a
 * given string in a vector.
 *
 * @params:
 *  - string: s
 *  - string: pattern
 *
 *  @returns:
 *  - vector<string> result
 */
auto getMatchesList(std::string s, std::string pattern) -> std::list<std::string>;

/**
 * Returns every match found on a given regex pattern in a
 * given string, converted by a given function in a vector.
 *
 * @params:
 *  - string: s
 *  - string: pattern
 *  - function: convert(string) -> T
 *
 *  @returns:
 *  - vector<T> result
 */
template <typename T>
auto getMatches(std::string s, std::string pattern, std::function<T(const std::string&)> convert)
    -> std::vector<T>
{
    std::regex rpattern(pattern);
    std::sregex_iterator it(s.begin(), s.end(), rpattern);
    std::sregex_iterator end;

    std::vector<T> result;

    while (it != end) {
        std::string match = it->str(1);
        result.push_back(convert(match));
        ++it;
    }

    return result;
}

/**
 * Returns every match found on a given regex pattern in a
 * given string, converted by a given function in a list.
 *
 * @params:
 *  - string: s
 *  - string: pattern
 *  - function: convert(string) -> T
 *
 *  @returns:
 *  - list<T> result
 */
template <typename T>
auto getMatchesList(
    std::string s, std::string pattern, std::function<T(const std::string&)> convert)
    -> std::list<T>
{
    std::regex rpattern(pattern);
    std::sregex_iterator it(s.begin(), s.end(), rpattern);
    std::sregex_iterator end;

    std::list<T> result;

    while (it != end) {
        std::string match = it->str(1);
        result.push_back(convert(match));
        ++it;
    }

    return result;
}

/**
 * Returns every match found for splitting a given string s
 * with anything that matches the given pattern, stored in a vector.
 *
 * @params:
 *  - string: s
 *  - string: pattern
 *
 *  @returns:
 *  - vector<string> result
 */
auto splitToVec(std::string s, std::string pattern) -> std::vector<std::string>;



/**
 * Returns every match found for splitting a given string s
 * with anything that matches the given pattern, stored in a list.
 *
 * @params:
 *  - string: s
 *  - string: pattern
 *
 *  @returns:
 *  - list<string> result
 */
auto splitToList(std::string s, std::string pattern) -> std::list<std::string>;



}
