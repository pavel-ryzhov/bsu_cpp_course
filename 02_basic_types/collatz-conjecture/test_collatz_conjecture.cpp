#include "collatz_conjecture.h"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("Simple") {
    CHECK(0 == IterationsToConverge(1));
    CHECK(14 == IterationsToConverge(11));
    CHECK(9 == IterationsToConverge(12));
    CHECK(20 == IterationsToConverge(19));
    CHECK(261 == IterationsToConverge(6171));
    CHECK(258 == IterationsToConverge(999'999));
    CHECK(524 == IterationsToConverge(837'799));
    CHECK(1348 == IterationsToConverge(989'345'275'647));
}

TEST_CASE("Non natural") {
    CHECK_FALSE(IterationsToConverge(0).has_value());
    CHECK_FALSE(IterationsToConverge(-1).has_value());
}
