#pragma once

#include <cstddef>
#include <cstdint>
#include <optional>

inline std::optional<int64_t> IterationsToConverge(int64_t n) {
    size_t counter = 0;
    for (; counter < 100'000 && n != 1; counter++) {
        if (n % 2 == 0) {
            n /= 2;
        } else {
            n = 3 * n + 1;
        }
    }
    return n == 1 ? std::optional(counter) : std::nullopt;
}
