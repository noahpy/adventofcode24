
#include <cstddef>
#include <string>

namespace nutils {

size_t absDiff(size_t a, size_t b)
{
    if (a < b) {
        return b - a;
    }
    return a - b;
}


// stoi without optional arguments
int stringToInt(const std::string& s){
    return std::stoi(s);
}

// stol without optional arguments
size_t stringToLong(const std::string& s){
    return std::stol(s);
}

// stod without optional arguments
double stringToDouble(const std::string& s){
    return std::stod(s);
}

// stof without optional arguments
float stringToFloat(const std::string& s){
    return std::stof(s);
}



}
