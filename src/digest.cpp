#include "digest/digest.hpp"
#include "digest/evp_ctx.hpp"

std::string hex(const std::vector<unsigned char>& digest) {
    std::string result;
    char buffer[3];
    for (unsigned int i = 0; i < digest.size() ; ++i) {
        sprintf(buffer, "%02hx", digest[i]);
        result.append(buffer);
    }
    return result;
}

std::vector<unsigned char> sha256(const std::string& input) {
    evp_ctx ctx;
    return ctx.digest(EVP_sha256(), input);
}

std::vector<unsigned char> sha512(const std::string& input, const std::vector<unsigned char>& pkey) {
    evp_ctx ctx;
    return ctx.sign(EVP_sha512(), input, pkey);
}