#pragma once

#include <cstddef>
#include <vector>

inline int NumberOfCommonElements(const std::vector<int>& lhs, const std::vector<int>& rhs) {
    size_t i = 0;
    size_t j = 0;
    int result = 0;
    while (i < lhs.size() && j < rhs.size()) {
        if (lhs[i] < rhs[j]) {
            i++;
        } else if (lhs[i] > rhs[j]) {
            j++;
        } else {
            result++;
            i++;
            j++;
        }
    }
    return result;
}
