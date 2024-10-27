#pragma once

#include "function.h"

#include <cstdint>
#include <string>

inline std::string ToBinaryString(int64_t n, char symbol0, char symbol1) {
    std::string result;
    while (n > 0) {
        result += (n % 2) != 0 ? symbol1 : symbol0;
        n /= 2;
    }
    return result;
}

inline std::string GenerateAsSequence(int n) {
    std::string result;
    int64_t a = 1;
    for (int i = 0; i < n; ++i) {
        result.append(ToBinaryString(a, ' ', '#'));
        result.push_back('\n');
        a = F(a);
    }
    return result;
}

inline std::string GenerateAsFunction(int n) {
    std::string result;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j <= i; ++j) {
            int num = 0;
            int denom = 0;
            for (int k = 2; k <= i; k *= 2) {
                num += i / k;
                denom += ((i - j) / k) + (j / k);
            }
            if (num == denom) {
                result.push_back('#');
            } else {
                result.push_back(' ');
            }
        }
        result.push_back('\n');
    }
    return result;
}
