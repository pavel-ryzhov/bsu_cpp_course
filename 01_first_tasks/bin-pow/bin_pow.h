#pragma once

#include <cstdint>

inline int32_t MultWithMod(int32_t a, int64_t b, int32_t c) {
    return static_cast<int32_t>(((a % c) * (b % c)) % c);
}

inline int32_t BinPow(int32_t a, int64_t b, int32_t c) {
    int32_t result = 1;
    while (b > 0) {
        if (b % 2 == 1) {
            result = MultWithMod(result, a, c);
        }
        a = MultWithMod(a, a, c);
        b /= 2;
    }
    return result % c;
}
