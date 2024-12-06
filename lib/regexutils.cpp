
#include <list>
#include <optional>
#include <regex>

namespace reutils {

auto getMatch(std::string s, std::string pattern) -> std::optional<std::string>
{
    std::regex rpattern(pattern);
    std::sregex_iterator it(s.begin(), s.end(), rpattern);
    std::sregex_iterator end;

    std::vector<std::string> result;

    if (it != end) {
        return std::make_optional(it->str(1));
    }

    return std::nullopt;
}

auto getMatches(std::string s, std::string pattern) -> std::vector<std::string>
{
    std::regex rpattern(pattern);
    std::sregex_iterator it(s.begin(), s.end(), rpattern);
    std::sregex_iterator end;

    std::vector<std::string> result;

    while (it != end) {
        std::string match = it->str(1);
        result.push_back(match);
        ++it;
    }

    return result;
}

auto getMatchesList(std::string s, std::string pattern) -> std::list<std::string>
{
    std::regex rpattern(pattern);
    std::sregex_iterator it(s.begin(), s.end(), rpattern);
    std::sregex_iterator end;

    std::list<std::string> result;

    while (it != end) {
        std::string match = it->str(1);
        result.push_back(match);
        ++it;
    }

    return result;
}

auto splitToVec(std::string s, std::string pattern) -> std::vector<std::string>
{
    std::regex rpattern(pattern);
    std::sregex_token_iterator it(s.begin(), s.end(), rpattern, -1);
    std::sregex_token_iterator end;

    std::vector<std::string> result;

    while (it != end) {
        std::string match = it->str();
        result.push_back(match);
        ++it;
    }

    return result;
}

auto splitToList(std::string s, std::string pattern) -> std::list<std::string>
{
    std::regex rpattern(pattern);
    std::sregex_token_iterator it(s.begin(), s.end(), rpattern, -1);
    std::sregex_token_iterator end;

    std::list<std::string> result;

    while (it != end) {
        std::string match = it->str();
        result.push_back(match);
        ++it;
    }

    return result;
}

}
