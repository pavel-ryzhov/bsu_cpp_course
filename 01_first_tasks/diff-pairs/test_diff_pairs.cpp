#include "diff_pairs.h"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("Your test here") {
    REQUIRE(11 == CountPairs({3, 3, 4, 8, 4, 5, 6, 9, 9, 3, 9}, 12));
}
