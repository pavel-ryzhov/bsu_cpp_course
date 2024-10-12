#pragma once

#include <cmath>
#include <cstdint>

inline int64_t ArithmeticMean(int64_t a, int64_t b) {
    const long double a1 = static_cast<long double>(a) / 2.0;
    const long double b1 = static_cast<long double>(b) / 2.0;
    return static_cast<int64_t>(a > b ? std::ceil(a1 + b1) : std::floor(a1 + b1));
}
