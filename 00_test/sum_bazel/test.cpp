#include "sum.h"

#include <catch2/catch_message.hpp>
#include <catch2/catch_test_macros.hpp>
#include <cstdint>
#include <type_traits>

TEST_CASE("Simple") {
    REQUIRE(5 == Sum(2, 3));
}

TEST_CASE("Signature") {
    INFO("Do not change Sum signature");
    static_assert(
        std::is_same_v<decltype(&Sum), int64_t (*)(int32_t, int32_t)>, "Wrong signature!");
}
