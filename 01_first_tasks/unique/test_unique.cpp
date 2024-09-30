#include "unique.h"

#include <algorithm>
#include <catch2/catch_test_macros.hpp>
#include <random>
#include <vector>

TEST_CASE("Simple") {
    {
        const std::vector test{1, 2, 2, 3, 3, 3};
        const std::vector expected{1, 2, 3};
        REQUIRE(expected == Unique(test));
    }
    {
        const std::vector test{1, 1, 1, 1};
        const std::vector expected{1};
        REQUIRE(expected == Unique(test));
    }
    {
        const std::vector test{1, 2, 3, 4};
        const std::vector expected{1, 2, 3, 4};
        REQUIRE(expected == Unique(test));
    }
    {
        const std::vector test{1, 1, 2, 2, 2, 3};
        const std::vector expected{1, 2, 3};
        REQUIRE(expected == Unique(test));
    }
    {
        const std::vector test{3, 2, 2, 2, 2, 1};
        const std::vector expected{3, 2, 1};
        REQUIRE(expected == Unique(test));
    }
    {
        const std::vector test{1, 1};
        const std::vector expected{1};
        REQUIRE(expected == Unique(test));
    }
}

TEST_CASE("Empty") {
    {
        const std::vector<int> test;
        const std::vector<int> expected;
        REQUIRE(expected == Unique(test));
    }
    {
        const std::vector test{0};
        const std::vector expected{0};
        REQUIRE(expected == Unique(test));
    }
}

TEST_CASE("Big") {
    std::default_random_engine generator;  // NOLINT(cert-msc32-c,cert-msc51-cpp)
    std::uniform_int_distribution random_element(-100, 100);

    std::vector<int> input;
    input.reserve(128LL * 1024);
    for (auto i = 0; i < 128 * 1024; i++) {
        input.push_back(random_element(generator));
    }

    std::ranges::sort(input);

    auto expected = input;
    auto end = std::unique(expected.begin(), expected.end());
    expected.erase(end, expected.end());

    REQUIRE(expected == Unique(input));
}
