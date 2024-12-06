
#include <string>

namespace stutils{

    /**
     * Repeat a given string n times.
     *
     * @params:
     *  - size_t: n
     *  - string: s
     *  @returns:
     *   - string: result
     */
    auto repeat(size_t n, std::string s) -> std::string;

    /**
     * Repeat a given string n times, with a given
     * delimiter string inbetween each repetition.
     *
     * @params:
     *  - size_t: n
     *  - string: s
     *  - string: delimiter
     *  @returns:
     *   - string: result
     */
    auto repeat(size_t n, std::string s, std::string delimiter) -> std::string;

     /**
     * Repeat a given string n times, with a given
     * delimiter char inbetween each repetition.
     *
     * @params:
     *  - size_t: n
     *  - string: s
     *  - char: delimiter
     *  @returns:
     *   - string: result
     */
    auto repeat(size_t n, std::string s, char delimiter) -> std::string;


}
