#ifndef _EVP_CTX_HPP_
#define _EVP_CTX_HPP_

#include <openssl/evp.h>
#include <memory>
#include <vector>

class evp_ctx {
public:
    struct deleter {
        void operator()(EVP_MD_CTX* ctx) const;
    };

    struct key_deleter {
        void operator()(EVP_PKEY* key) const;
    };

    evp_ctx();
    ~evp_ctx() = default;

    std::vector<unsigned char> digest(const EVP_MD* type, const std::string& input);

    std::vector<unsigned char> sign(const EVP_MD* type, const std::string& input, const std::vector<unsigned char>& pkey);

private:
    std::unique_ptr<EVP_MD_CTX, deleter> ctx_;
};

#endif