#include "range.h"

#include <catch2/catch_test_macros.hpp>
#include <limits>
#include <vector>

TEST_CASE("Simple") {
    {
        const std::vector expected{2, 3, 4};
        REQUIRE(expected == Range(2, 5, 1));
    }
    {
        const std::vector expected{1, 3};
        REQUIRE(expected == Range(1, 5, 2));
    }
    {
        const std::vector expected{-9, -4, 1, 6};
        REQUIRE(expected == Range(-9, 10, 5));
    }
}

TEST_CASE("SimpleReverse") {
    {
        const std::vector expected{5, 4, 3};
        REQUIRE(expected == Range(5, 2, -1));
    }
    {
        const std::vector expected{5, 3};
        REQUIRE(expected == Range(5, 1, -2));
    }
    {
        const std::vector expected{7};
        REQUIRE(expected == Range(7, 6, -3));
    }
}

TEST_CASE("Empty") {
    REQUIRE(Range(0, 0, 2).empty());
    REQUIRE(Range(2, 2, 1).empty());
    REQUIRE(Range(10, 10, -2).empty());
}

TEST_CASE("EmptyInf") {
    REQUIRE(Range(3, 7, -1).empty());
    REQUIRE(Range(3, 4, 0).empty());
    REQUIRE(Range(5, -5, 2).empty());
    REQUIRE(Range(3, -7, 0).empty());
}

TEST_CASE("NumericLimits") {
    {
        const std::vector<int> expected{-2'147'483'648, -147'483'648, 1'852'516'352};
        REQUIRE(
            expected ==
            Range(std::numeric_limits<int>::min(), std::numeric_limits<int>::max(), 2'000'000'000));
    }
    {
        const std::vector<int> expected{2'147'483'647, 147'483'647, -1'852'516'353};
        REQUIRE(
            expected ==
            Range(
                std::numeric_limits<int>::max(), std::numeric_limits<int>::min(), -2'000'000'000));
    }
    {
        const std::vector<int> expected{};
        REQUIRE(
            expected ==
            Range(
                std::numeric_limits<int>::max(), std::numeric_limits<int>::max(), -2'000'000'000));
        REQUIRE(
            expected ==
            Range(
                std::numeric_limits<int>::min(), std::numeric_limits<int>::min(), -2'000'000'000));
    }
}
