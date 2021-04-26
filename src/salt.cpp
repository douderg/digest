#include "digest/salt.hpp"

std::vector<char> salt::valid = salt::make_alnum();

std::vector<char> salt::make_alnum() {
    std::vector<char> digits;
    std::string s = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    for (auto c : s) {
        digits.push_back(c);
    }
    return digits;
}
