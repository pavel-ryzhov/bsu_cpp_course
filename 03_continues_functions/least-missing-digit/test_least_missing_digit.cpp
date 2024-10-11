#include "least_missing_digit.h"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("Simple") {
    CHECK(LeastMissingDigit(120) == 3);
    CHECK(LeastMissingDigit(0) == 1);
}
