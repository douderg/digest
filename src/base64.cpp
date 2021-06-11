#include <digest/base64.hpp>
#include <openssl/evp.h>
#include <stdexcept>

namespace base64 {

std::string encode(const std::vector<unsigned char>& bytes) {
    int expect = 4 * ((bytes.size() + 2) / 3);
    std::string result(expect + 1, '\0');
    int actual = EVP_EncodeBlock(reinterpret_cast<unsigned char *>(result.data()), bytes.data(), bytes.size());
    if (actual != expect) { 
        throw std::runtime_error("failed to encode base64");
    }
    result.pop_back();
    return result;
}

std::vector<unsigned char> decode(const std::string& input) {
    int expect = 3 * input.size() / 4;
    std::vector<unsigned char> result(expect + 1, '\0');
    int actual = EVP_DecodeBlock(result.data(), reinterpret_cast<const unsigned char *>(input.c_str()), input.size());
    if (actual != expect) { 
        throw std::runtime_error("failed to decode base64");
    }
    result.pop_back();
    return result;
}

}