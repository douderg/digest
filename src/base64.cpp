#include <digest/base64.hpp>
#include <openssl/evp.h>
#include <stdexcept>

namespace base64 {

std::string encode(const std::vector<unsigned char>& bytes) {
    size_t expect = 4 * ((bytes.size() + 2) / 3);
    std::vector<unsigned char> data(expect + 1, '\0');
    size_t actual = EVP_EncodeBlock(data.data(), bytes.data(), bytes.size());
    if (actual != expect) { 
        throw std::runtime_error("failed to encode base64");
    }
    data.pop_back();
    return std::string(data.begin(), data.end());
}

std::vector<unsigned char> decode(const std::string& input) {
    size_t expect = 3 * input.size() / 4;
    std::vector<unsigned char> result(expect + 1, '\0');
    size_t actual = EVP_DecodeBlock(result.data(), reinterpret_cast<const unsigned char *>(input.c_str()), input.size());
    if (actual != expect) { 
        throw std::runtime_error("failed to decode base64");
    }
    result.pop_back();
    return result;
}

}