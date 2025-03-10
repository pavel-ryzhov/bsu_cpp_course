#include <catch2/catch_test_macros.hpp>

#include "local_max.h"

#include <vector>

TEST_CASE("Your test") {
    std::vector a = {1, 7, 3, 9, 10};
    REQUIRE(*LocalMax(a.begin(), a.end()) == 7);
}
