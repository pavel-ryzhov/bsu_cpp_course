#pragma once

#include <algorithm>
#include <cmath>
#include <cstdint>

enum class RootCount : uint8_t { kZero, kOne, kTwo, kInf };

struct Roots {
    RootCount count;
    double first;
    double second;
};

inline Roots SolveQuadratic(int a, int b, int c) {
    if (a == 0 && b == 0 && c == 0) [[unlikely]] {
        return Roots{RootCount::kInf};
    }
    if (a == 0 && b == 0) {
        return Roots{RootCount::kZero};
    }
    if (a == 0) {
        return Roots{RootCount::kOne, static_cast<double>(-c) / b};
    }
    const int d = (b * b) - (4 * a * c);
    if (d < 0) {
        return Roots{RootCount::kZero};
    }
    if (d == 0) {
        return Roots{RootCount::kOne, -b / (2.0 * a)};
    }
    const double r1 = (-b - std::sqrt(d)) / (2.0 * a);
    const double r2 = (-b + std::sqrt(d)) / (2.0 * a);
    return Roots{RootCount::kTwo, std::min(r1, r2), std::max(r1, r2)};
}
