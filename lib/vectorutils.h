
#include <iostream>
#include <map>
#include <set>
#include <vector>

namespace veutils {

/**
 * Takes a vector of the element type T and converts it to
 * a set of type T.
 *
 * @param vecto<T> v
 *
 * @return set<T> result
 */
template <typename T>
std::set<T> vecToSet(std::vector<T> v)
{
    std::set<T> result;
    for (T t : v) {
        result.insert(t);
    }
    return result;
}

/*
 * Takes one iterable type V with element type E and returns
 * if it has duplicate elements. Returns true if there is such
 * element, else false. Returns also true if the method fails for some
 * reason.
 *
 * @param V<E> a
 *
 * @return bool result
 */
template <typename V, typename E>
bool existsDupl(V v)
{
    try {
        std::map<E, int> m;
        for (E e : v) {
            if (m.find(e) == m.end()) {
                m.insert({ e, 1 });
            } else {
                return true;
            }
        }
        return false;
    } catch (std::exception e) {
        std::cout << e.what();
        return true;
    }
}

/**
 * Takes two vectors with the common element type T, and returns
 * a vector with common elements. This method is not optimized and
 * does not remove duplicate commons.
 *
 * @param vector<T> v1
 * @param vector<T> v2
 *
 * @result vector<T> result
 */
template <typename T>
std::vector<T> getIntersect(std::vector<T> v1, std::vector<T> v2)
{
    std::vector<T> result;
    for (size_t i = 0; i < v1.size(); i++) {
        if (find(v2.begin(), v2.end(), v1.at(i)) != v2.end()) {
            result.push_back(v1.at(i));
        }
    }
    return result;
}

}
