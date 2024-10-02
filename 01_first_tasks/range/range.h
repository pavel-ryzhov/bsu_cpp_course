#pragma once

#include <cstdint>
#include <vector>

inline std::vector<int> Range(int from, int to, int step) {
    std::vector<int> v;
    if (to > from == step > 0) {
        for (int64_t i = from; step < 0 ? (i > to) : (i < to); i += step) {
            v.push_back(static_cast<int>(i));
        }
    }
    return v;
}
