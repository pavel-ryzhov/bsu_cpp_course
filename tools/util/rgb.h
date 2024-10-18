#pragma once

#include <cassert>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <format>
#include <ostream>
#include <tuple>

struct RGB {
    uint8_t r;
    uint8_t g;
    uint8_t b;
};

inline double PixelDistance(const RGB& lhs, const RGB& rhs) {
    auto dr = lhs.r - rhs.r;
    auto dg = lhs.g - rhs.g;
    auto db = lhs.b - rhs.b;
    return std::sqrt(dr * dr + dg * dg + db * db);
}

[[maybe_unused]] static const RGB kBlack{0, 0, 0};
[[maybe_unused]] static const RGB kGray{128, 128, 128};
[[maybe_unused]] static const RGB kLightgray{85, 85, 85};
[[maybe_unused]] static const RGB kWhite{255, 255, 255};
[[maybe_unused]] static const RGB kRed{255, 0, 0};
[[maybe_unused]] static const RGB kGreen{0, 255, 0};
[[maybe_unused]] static const RGB kBlue{0, 0, 255};
[[maybe_unused]] static const RGB kYellow{255, 255, 0};
[[maybe_unused]] static const RGB kCyan{0, 255, 255};
[[maybe_unused]] static const RGB kPurple{255, 0, 255};

inline bool operator==(const RGB& lhs, const RGB& rhs) {
    return std::tie(lhs.r, lhs.g, lhs.b) == std::tie(rhs.r, rhs.g, rhs.b);
}

inline std::ostream& operator<<(std::ostream& os, const RGB& color) {
    os << std::format("#{:02x}{:02x}{:02x}", color.r, color.g, color.b);
    return os;
}
