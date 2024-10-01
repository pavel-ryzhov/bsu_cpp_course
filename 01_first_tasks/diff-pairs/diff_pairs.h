#pragma once

#include <cstddef>
#include <unordered_map>
#include <vector>

inline size_t CountPairs(const std::vector<int>& data, int x) {
    std::unordered_map<int, size_t> map;
    size_t count = 0;
    for (const int d : data) {
        if (map.find(d) != map.end()) {
            count += map[d];
        }
        map[x - d]++;
    }
    return count;
}
