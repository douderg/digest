#ifndef _SALT_HPP_
#define _SALT_HPP_

#include <string>
#include <random>
#include <algorithm>

class salt {
    static std::vector<char> make_alnum();
    static std::vector<char> valid;
public:
    template <class RNG>
    static std::string create(RNG&& rng, size_t length) {
        std::uniform_int_distribution<unsigned char> dist(0, valid.size());
        std::string result(length, ' ');
        std::generate(result.begin(), result.end(), [&]() -> char {
            return valid[dist(rng)];
        });
        return result;
    }
};

#endif