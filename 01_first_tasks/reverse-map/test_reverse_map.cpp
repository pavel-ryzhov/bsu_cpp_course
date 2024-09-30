#include "reverse_map.h"

#include <catch2/catch_test_macros.hpp>
#include <string>
#include <unordered_map>

using Map = std::unordered_map<std::string, int>;
using ReversedMap = std::unordered_map<int, std::string>;

TEST_CASE("Simple") {
    {
        const Map test{{"aba", 3}, {"caba", 1}, {"test", 2}};
        const ReversedMap expected{{1, "caba"}, {2, "test"}, {3, "aba"}};
        REQUIRE(expected == ReverseMap(test));
    }
    {
        const Map test{{"", 0}, {"1", 1}};
        const ReversedMap expected{{0, ""}, {1, "1"}};
        REQUIRE(expected == ReverseMap(test));
    }
}

TEST_CASE("Empty") {
    const Map test;
    const ReversedMap expected;
    REQUIRE(expected == ReverseMap(test));
}
