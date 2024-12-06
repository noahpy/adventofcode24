
#include <sstream>
#include <string>

namespace stutils {
auto repeat(size_t n, std::string s) -> std::string
{
    std::ostringstream os;
    for (size_t i = 0; i < n; i++)
        os << s;
    return os.str();
}


auto repeat(size_t n, std::string s, std::string delimiter) -> std::string{
    std::ostringstream os;
    for (size_t i = 0; i < n; i++){
        os << s;
        if (i < n-1){
            os << delimiter;
        }
    }
    return os.str();

}

auto repeat(size_t n, std::string s, char delimiter) -> std::string{
    std::ostringstream os;
    for (size_t i = 0; i < n; i++){
        os << s;
        if (i < n-1){
            os << delimiter;
        }
    }
    return os.str();

}

}
