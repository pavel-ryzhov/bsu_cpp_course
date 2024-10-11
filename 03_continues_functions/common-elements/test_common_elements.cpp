#include "common_elements.h"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("Simple") {
    CHECK(NumberOfCommonElements({0, 2, 3, 5, 11}, {2, 4, 5, 6}) == 2);
}
