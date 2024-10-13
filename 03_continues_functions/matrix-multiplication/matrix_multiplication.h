#pragma once

#include <cstddef>
#include <cstdint>
#include <vector>

inline std::vector<std::vector<int32_t>> MultiplyMatrices(
    const std::vector<std::vector<int32_t>>& lhs, const std::vector<std::vector<int32_t>>& rhs) {
    const size_t l = lhs.size();
    const size_t m = rhs.size();
    const size_t n = rhs.front().size();
    std::vector result(l, std::vector<int32_t>());
    for (size_t i = 0; i < l; i++) {
        for (size_t j = 0; j < n; j++) {
            int32_t a = 0;
            for (size_t r = 0; r < m; r++) {
                a += lhs[i][r] * rhs[r][j];
            }
            result[i].push_back(a);
        }
    }
    return result;
}