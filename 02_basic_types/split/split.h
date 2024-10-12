#pragma once

#include <cstddef>
#include <string>
#include <vector>

inline std::vector<std::string> Split(const std::string& string, const std::string& delimiter) {
    if (string.empty()) {
        return {};
    }
    std::vector<std::string> result;
    size_t pos = 0;
    size_t p = 0;
    while ((p = string.find(delimiter, p)) != std::string::npos) {
        result.push_back(string.substr(pos, p - pos));
        p += delimiter.size();
        pos = p;
    }
    result.push_back(string.substr(pos));
    return result;
}
