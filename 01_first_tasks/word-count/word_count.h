#pragma once

#include <cctype>
#include <cstddef>
#include <string>
#include <unordered_map>

inline size_t DifferentWordsCount(const std::string& text) {
    std::unordered_map<std::string, size_t> map;
    std::string word;
    for (const char& c : text) {
        if (static_cast<bool>(std::isalpha(c))) {
            word += static_cast<char>(std::tolower(c));
        } else if (!word.empty()) {
            map[word]++;
            word.clear();
        }
    }
    if (!word.empty()) {
        map[word]++;
        word.clear();
    }
    return map.size();
}
