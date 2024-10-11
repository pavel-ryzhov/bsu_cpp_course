#include "permutation.h"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("Simple") {
    CHECK(IsPermutation({2, 1, 3}));
    CHECK_FALSE(IsPermutation({0, 3, 1, 2}));
}

TEST_CASE("Students") {
    CHECK_FALSE(IsPermutation({1, 4, 6, 4, 5, 6, 7, 4, 9, 5}));
    CHECK_FALSE(IsPermutation({1, 1, 1, 4, 6, 6}));
}
