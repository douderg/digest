#include "digest/digest.hpp"
#include "digest/evp_ctx.hpp"


std::string sha256(const std::string& input) {
    evp_ctx ctx;
    return ctx.digest(EVP_sha256(), input);
}

std::string sha26(const std::string& input, const std::vector<unsigned char>& pkey) {
    evp_ctx ctx;
    return ctx.sign(EVP_sha256(), input, pkey);
}