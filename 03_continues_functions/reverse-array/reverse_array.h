#pragma once

#include <cstddef>
#include <utility>
#include <vector>

inline void ReverseArray(std::vector<int>& array) {
    for (size_t i = 0; i < array.size() / 2; i++) {
        std::swap(array[i], array[array.size() - i - 1]);
    }
}
