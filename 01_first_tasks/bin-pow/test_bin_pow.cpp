#include "bin_pow.h"

#include <catch2/catch_message.hpp>
#include <catch2/catch_test_macros.hpp>
#include <cstdint>
#include <limits>
#include <type_traits>

TEST_CASE("Small") {
    REQUIRE(8 == BinPow(2, 3, 19));
    REQUIRE(1 == BinPow(3, 0, 19));
    REQUIRE(27 == BinPow(3, 3, 100));
    REQUIRE(1 == BinPow(3, 4, 20));
    REQUIRE(536 == BinPow(4, 8, 1000));
}

TEST_CASE("Big") {
    REQUIRE(1 == BinPow(1, 374'834'758'345LL, 129'237));
    REQUIRE(719'476'260 == BinPow(2, 1'000'000'000'000'000'000LL, 1'000'000'007));
    REQUIRE(43'181'159 == BinPow(17'239, 1'000'000'000'000'000LL - 1, 100'000'000));
    REQUIRE(78'360 == BinPow(203'042'322, 82'392'839'238'824'787LL, 92'374));
}

TEST_CASE("NumericLimits") {
    REQUIRE(
        2'140'880'313 == BinPow(
                             std::numeric_limits<int>::max(), std::numeric_limits<int64_t>::max(),
                             std::numeric_limits<int>::max() - 5));
    REQUIRE(
        -939'621'510 == BinPow(
                            std::numeric_limits<int>::min(), std::numeric_limits<int64_t>::max(),
                            std::numeric_limits<int>::max() - 5));
}

TEST_CASE("Signature") {
    INFO("Do not change Sum signature");
    static_assert(std::is_same_v<decltype(&BinPow), int32_t (*)(int32_t, int64_t, int32_t)>);
}
