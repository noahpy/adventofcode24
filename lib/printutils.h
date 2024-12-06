
#include <functional>
#include <iostream>
#include <list>
#include <sstream>
#include <string>
#include <vector>

namespace prutils {

/**
 * Takes a vector of the element type T and tries to print out
 * its elements. If the element type does not support a cast to
 * string, this method will fail.
 *
 * @param vector<T> v
 */
template <typename T>
void printVector(std::vector<T> v)
{
    std::cout << "{";
    for (size_t i = 0; i < v.size(); i++) {
        std::cout << v.at(i);
        if (i < v.size() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << "}" << std::endl;
}

/**
 * Takes a vector of the element type T and tries to print out
 * its elements.
 * @params:
 * - vector<T> v
 * - function: to_str(T) -> string
 */
template <typename T>
void printVector(std::vector<T> v, std::function<std::string(T)> to_str)
{
    std::cout << "{";
    for (size_t i = 0; i < v.size(); i++) {
        std::cout << to_str(v.at(i));
        if (i < v.size() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << "}" << std::endl;
}

/**
 * Takes a list of the element type T and tries to print out
 * its elements.
 * @params:
 * - list<T> v
 * - function: to_str(T) -> string
 */
template <typename T>
void printList(std::list<T> v, std::function<std::string(T)> to_str)
{
    std::cout << "{";
    for (size_t i = 0; i < v.size(); i++) {
        std::cout << to_str(v.at(i));
        if (i < v.size() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << "}" << std::endl;
}

/**
 * Convert a pair to a string, where the elements
 * are delimited by a column.
 */
template <typename A>
auto pairToString(std::pair<A, A> p) -> std::string
{
    std::stringstream ss;
    ss << "(" << p.first << ":" << p.second << ")";
    return ss.str();
}

/**
 * Convert a pair to a string, where the elements
 * are delimited by a column.
 */
template <typename A, typename B>
auto pairToString(std::pair<A, B> p) -> std::string
{
    std::stringstream ss;
    ss << "(" << p.first << ":" << p.second << ")";
    return ss.str();
}

template <typename A>
auto vecToString(std::vector<A> as) -> std::string
{
    std::stringstream ss;
    for (A a : as) {
        ss << a;
    }
    return ss.str();
}

template <typename A>
auto vecToStringPretty(std::vector<A> as) -> std::string
{
    std::stringstream ss;
    ss << "{";
    for (size_t i = 0; i < as.size(); i++) {
        ss << as[i];
        if (i < as.size() - 1)
            ss << ", ";
    }
    ss << "}";
    return ss.str();
}

}
