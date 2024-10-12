#pragma once

#include <cmath>
#include <cstdint>

inline int Bitlen(int64_t n) {
    return static_cast<int>(std::floor(std::log2(n)) + 1);
}

inline int64_t F(int64_t n) {
    std::int64_t result = 0;
    const int i = Bitlen(n);
    for (int j = 0; j <= i; ++j) {
        int num = 0;
        int denom = 0;
        for (int k = 2; k <= i; k *= 2) {
            num += i / k;
            denom += ((i - j) / k) + (j / k);
        }
        result *= 2;
        if (num == denom) {
            result++;
        }
    }
    return result;
}