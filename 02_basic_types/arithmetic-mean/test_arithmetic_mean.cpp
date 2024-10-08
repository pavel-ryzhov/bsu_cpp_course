#include "arithmetic_mean.h"

#include <catch2/catch_test_macros.hpp>
#include <cstdint>
#include <limits>

TEST_CASE("Small") {
    REQUIRE(4 == ArithmeticMean(4, 4));

    REQUIRE(3 == ArithmeticMean(2, 4));
    REQUIRE(3 == ArithmeticMean(4, 2));

    REQUIRE(3 == ArithmeticMean(2, 5));
    REQUIRE(4 == ArithmeticMean(5, 2));

    REQUIRE(5 == ArithmeticMean(5, 4));
    REQUIRE(4 == ArithmeticMean(4, 5));

    REQUIRE(-6 == ArithmeticMean(2, -15));
    REQUIRE(-7 == ArithmeticMean(-15, 2));

    REQUIRE(50'250 == ArithmeticMean(100'500, -1));
    REQUIRE(50'249 == ArithmeticMean(-1, 100'500));
}

TEST_CASE("NumericLimits") {
    REQUIRE(
        std::numeric_limits<int64_t>::min() ==
        ArithmeticMean(std::numeric_limits<int64_t>::min(), std::numeric_limits<int64_t>::min()));
    REQUIRE(
        -1 ==
        ArithmeticMean(std::numeric_limits<int64_t>::min(), std::numeric_limits<int64_t>::max()));
    REQUIRE(
        0 ==
        ArithmeticMean(std::numeric_limits<int64_t>::max(), std::numeric_limits<int64_t>::min()));
    REQUIRE(
        std::numeric_limits<int64_t>::max() ==
        ArithmeticMean(std::numeric_limits<int64_t>::max(), std::numeric_limits<int64_t>::max()));

    REQUIRE(-4'611'686'018'427'387'903LL == ArithmeticMean(1, std::numeric_limits<int64_t>::min()));
    REQUIRE(-4'611'686'018'427'387'904LL == ArithmeticMean(std::numeric_limits<int64_t>::min(), 1));

    REQUIRE(4'611'686'018'427'387'904LL == ArithmeticMean(1, std::numeric_limits<int64_t>::max()));
    REQUIRE(4'611'686'018'427'387'904LL == ArithmeticMean(std::numeric_limits<int64_t>::max(), 1));

    constexpr const int64_t kBig{-117'070'077'343'371'727LL};
    REQUIRE(
        -4'670'221'057'099'073'768LL == ArithmeticMean(std::numeric_limits<int64_t>::min(), kBig));
    REQUIRE(
        -4'670'221'057'099'073'767LL == ArithmeticMean(kBig, std::numeric_limits<int64_t>::min()));

    REQUIRE(
        4'553'150'979'755'702'040LL == ArithmeticMean(std::numeric_limits<int64_t>::max(), kBig));
    REQUIRE(
        4'553'150'979'755'702'040LL == ArithmeticMean(kBig, std::numeric_limits<int64_t>::max()));
}
