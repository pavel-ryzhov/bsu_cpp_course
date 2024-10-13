#pragma once

#include <algorithm>
#include <vector>

inline bool IsPermutation(const std::vector<int>& array) {
    unsigned int result = 0;
    unsigned int max = 0;
    for (unsigned int i = 0; i < array.size(); i++) {
        const unsigned int d = array[i];
        max = std::max(max, d);
        result ^= d ^ (i + 1);
    }
    return result == 0 && array.size() == max;
}
