
#include <cstddef>
#include <iostream>
#include <queue>

namespace nutils {

/**
 * Takes two arguments any type that is capable of the modulo-operator (%) and
 * gives back the mathematically complete Modulo result a mod b.
 * If the type is not capable of the %-operator, it will simply return a.
 *
 * @param T a
 * @param T b
 *
 * @return T result
 */
template <typename T>
T modulo(T a, T b)
{
    try {
        const T result = a % b;
        return result >= 0 ? result : result + b;
    } catch (std::exception e) {
        std::cout << e.what();
        return a;
    }
}



/**
 * Calculate the absoulte difference between two given size_t a and b.
 *
 * @params:
 *  - size_t: a
 *  - size_t: b
 *
 *  @returns:
 *  - size_t: diff
 */
size_t absDiff(size_t a, size_t b);

// stoi without optional arguments
int stringToInt(const std::string& s);

// stol without optional arguments
size_t stringToLong(const std::string& s);

// stod without optional arguments
double stringToDouble(const std::string& s);

// stof without optional arguments
float stringToFloat(const std::string& s);
}
