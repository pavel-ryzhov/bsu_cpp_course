#pragma once

#include <string>
#include <unordered_map>
#include <utility>

inline std::unordered_map<int, std::string> ReverseMap(
    const std::unordered_map<std::string, int>& map) {
    std::unordered_map<int, std::string> result;
    for (const std::pair<std::string, int> e : map) {
        result[e.second] = e.first;
    }
    return result;
}
