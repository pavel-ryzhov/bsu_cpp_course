#include "permutations.h"

#include <algorithm>
#include <catch2/catch_test_macros.hpp>
#include <numeric>
#include <vector>

using Permutations = std::vector<std::vector<int>>;

TEST_CASE("Small") {
    {
        const Permutations expected{
          {0, 1, 2}, {0, 2, 1}, {1, 0, 2}, {1, 2, 0}, {2, 0, 1}, {2, 1, 0}};
        REQUIRE(expected == GeneratePermutations(3));
    }
    {
        const Permutations expected{{0}};
        REQUIRE(expected == GeneratePermutations(1));
    }
    {
        const Permutations expected{{0, 1}, {1, 0}};
        REQUIRE(expected == GeneratePermutations(2));
    }
}

TEST_CASE("Big") {
    const auto result = GeneratePermutations(8);

    std::vector<int> expected(8);
    std::iota(expected.begin(), expected.end(), 0);

    for (int i = 0;; ++i) {
        REQUIRE(expected == result[i]);
        if (!std::ranges::next_permutation(expected).found) {
            break;
        }
    }
}
