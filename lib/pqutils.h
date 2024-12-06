
#include <utility>

namespace pqutils{

template <typename T>
struct pairIntGreater {
    bool operator()(std::pair<T, int> a, std::pair<T, int> b) { return a.second > b.second; }
};

template <typename T>
struct pairIntLesser {
    bool operator()(std::pair<T, int> a, std::pair<T, int> b) { return a.second < b.second; }
};

template <typename T>
struct pairSizetGreater {
    bool operator()(std::pair<T, std::size_t> a, std::pair<T, std::size_t> b) { return a.second > b.second; }
};

template <typename T>
struct pairSizetLesser {
    bool operator()(std::pair<T, std::size_t> a, std::pair<T, std::size_t> b) { return a.second < b.second; }
};

}
