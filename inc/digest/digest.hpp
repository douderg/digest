#ifndef _DIGEST_HPP_
#define _DIGEST_HPP_

#include <string>
#include <vector>

std::string hex(const std::vector<unsigned char>& digest);

std::vector<unsigned char> sha256(const std::string& input);

std::vector<unsigned char> sha512(const std::string& input, const std::vector<unsigned char>& pkey);

#endif