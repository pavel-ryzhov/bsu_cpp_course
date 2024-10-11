#include "matrix_multiplication.h"

#include <catch2/catch_test_macros.hpp>
#include <cstdint>
#include <vector>

TEST_CASE("Simple") {
    const auto result = MultiplyMatrices(
        {{1, 0, 2}}, {
                       {2, 1},
                       {11, -5},
                       {1, -1},
                     });
    CHECK(result == std::vector<std::vector<int32_t>>{{4, -1}});
}
