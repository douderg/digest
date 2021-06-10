#include "digest/evp_ctx.hpp"
#include <stdexcept>
#include <cstring>

evp_ctx::evp_ctx():ctx_(EVP_MD_CTX_new(), deleter()) {
    if (!ctx_) {
        throw std::runtime_error("failed to initialize evp context");
    }
}

std::vector<unsigned char> evp_ctx::digest(const EVP_MD* type, const std::string& input) {
    if (!EVP_DigestInit_ex(ctx_.get(), type, NULL)) {
        throw std::runtime_error("failed to setup digest type");
    }
    if (!EVP_DigestUpdate(ctx_.get(), input.c_str(), input.size())) {
        throw std::runtime_error("failed to update digest");
    }
    unsigned char md[EVP_MAX_MD_SIZE];
    unsigned int len = 0;
    if (!EVP_DigestFinal_ex(ctx_.get(), md, &len)) {
        throw std::runtime_error("failed to compute digest");
    }
    return std::vector<unsigned char>(md, md + len);
}


std::vector<unsigned char> evp_ctx::sign(const EVP_MD* type, const std::string& input, const std::vector<unsigned char>& pkey) {
    std::unique_ptr<EVP_PKEY, key_deleter> key(EVP_PKEY_new_mac_key(EVP_PKEY_HMAC, NULL, pkey.data(), pkey.size()));
    if (!EVP_DigestSignInit(ctx_.get(), NULL, type, NULL, key.get())) {
        throw std::runtime_error("failed to setup digest type");
    }
    if (!EVP_DigestSignUpdate(ctx_.get(), input.c_str(), input.size())) {
        throw std::runtime_error("failed to update digest");
    }
    unsigned char md[EVP_MAX_MD_SIZE];
    size_t len = 0;
    if (!EVP_DigestSignFinal(ctx_.get(), md, &len)) {
        throw std::runtime_error("failed to compute digest");
    }
    return std::vector<unsigned char>(md, md + len);
}


void evp_ctx::deleter::operator()(EVP_MD_CTX* ctx) const {
    if (ctx) {
        EVP_MD_CTX_free(ctx);
    }
}

void evp_ctx::key_deleter::operator()(EVP_PKEY* key) const {
    if (key) {
        EVP_PKEY_free(key);
    }
}