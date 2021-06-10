#pragma once

#include <string>
#include <vector>

namespace base64 {

std::string encode(const std::vector<unsigned char>& bytes);
std::vector<unsigned char> decode(const std::string& input);

};