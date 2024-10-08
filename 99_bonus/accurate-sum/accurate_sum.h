#pragma once

#include <vector>

inline long double AccurateSum(const std::vector<long double>& data) {
    long double c = 0.0;
    for (auto x : data) {
        c += x;
    }
    return c;
}
