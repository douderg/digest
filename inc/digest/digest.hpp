#ifndef _DIGEST_HPP_
#define _DIGEST_HPP_

#include <string>
#include <vector>

std::string sha256(const std::string& input);
std::string sha26(const std::string& input, const std::vector<unsigned char>& pkey);

#endif