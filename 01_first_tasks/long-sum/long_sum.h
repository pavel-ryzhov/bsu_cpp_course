#pragma once

#include <cstddef>
#include <string>
#include <algorithm>

inline std::string LongSum(const std::string& a, const std::string& b) {
    std::string result;
    std::string a1;
    std::string b1;
    a1.assign(a.rbegin(), a.rend());
    b1.assign(b.rbegin(), b.rend());
    bool r = false;
    for (size_t i = 0; i < std::max(a.size(), b.size()); i++) {
        const int val1 = i < a1.size() ? a1[i] - '0' : 0;
        const int val2 = i < b1.size() ? b1[i] - '0' : 0;
        const int num = val1 + val2 + static_cast<int>(r);
        result += static_cast<char>(num % 10 + '0');
        r = num > 9;
    }
    if (r) {
        result += '1';
    }
    std::ranges::reverse(result);
    return result;
}
