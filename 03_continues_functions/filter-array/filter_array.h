#pragma once

#include <vector>

inline void FilterArray(std::vector<int>& array) {
    for (int i = static_cast<int>(array.size() - 1); i >= 0; i--) {
        if (array[i] == 0) {
            array.erase(array.begin() + i);
        }
    }
}
