#pragma once

#include <cstddef>
#include <cstdint>
#include <string>

inline bool IsValidCreditCardNumber(int64_t n) {
    int64_t sum1 = 0;
    int64_t sum2 = 0;
    const size_t l = std::to_string(n).size();
    for (size_t i = 0; i < l; i++) {
        int64_t c = n % 10;
        n /= 10;
        if (i % 2 == 0) {
            sum1 += c;
        } else {
            c *= 2;
            sum2 += c % 10 + c / 10;
        }
    }
    return (sum1 + sum2) % 10 == 0;
}
