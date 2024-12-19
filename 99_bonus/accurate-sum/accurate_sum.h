#pragma once

#include <cstddef>
#include <vector>

inline long double AccurateSum(const std::vector<long double>& data) {
    long double c = data[0];
    long double d = 0.0;
    for (size_t i = 1; i < data.size(); ++i) {
        const long double v1 = c + data[i];
        const long double v2 = v1 - c;
        const long double v3 = (c - (v1 - v2)) + (data[i] - v2);
        c = v1;
        d += v3;
    }
    return c + d;
}
