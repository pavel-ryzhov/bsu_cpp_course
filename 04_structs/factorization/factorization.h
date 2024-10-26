#pragma once

#include <cmath>
#include <cstdint>
#include <map>
#include <utility>
#include <vector>

inline std::vector<std::pair<int64_t, int>> Factorize(int64_t x) {
    std::map<int64_t, int> result;
    for (int64_t i = 2; i <= static_cast<int64_t>(std::sqrt(x)); i++) {
        while (x % i == 0) {
            result[i]++;
            x /= i;
        }
    }
    if (x != 1) {
        result[x]++;
    }
    auto v = std::vector<std::pair<int64_t, int>>();
    v.reserve(result.size());
    for (const auto& p : result) {
        v.emplace_back(p);
    }
    return v;
}