#include "rotate.h"

#include <catch2/catch_test_macros.hpp>
#include <vector>

TEST_CASE("Simple") {
    std::vector<int> array{1, 2, 3, 4, 5, 6};
    Rotate(array, 2);
    CHECK(array == std::vector<int>{3, 4, 5, 6, 1, 2});
}
