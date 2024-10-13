#pragma once

#include <set>

inline int LeastMissingDigit(int n) {
    std::set<int> digits;
    while (n > 0) {
        digits.insert(n % 10);
        n /= 10;
    }
    for (int i = 1; i < 10; i++) {
        if (!digits.contains(i)) {
            return i;
        }
    }
    return 0;
}
