#pragma once

#include <algorithm>
#include <cstddef>
#include <vector>

inline void PartitionBySign(std::vector<int>& array) {
    const size_t size = array.size();
    size_t index = 0;
    for (size_t i = 0; i < size; i++) {
        if (array[i] < 0) {
            for (size_t j = i; j > index; j--) {
                std::swap(array[j], array[j - 1]);
            }
            index++;
        }
    }
    for (size_t i = 0; i < size; i++) {
        if (array[i] == 0) {
            for (size_t j = i; j > index; j--) {
                std::swap(array[j], array[j - 1]);
            }
            index++;
        }
    }
}
