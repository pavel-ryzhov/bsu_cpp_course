#include "filter_array.h"

#include <catch2/catch_test_macros.hpp>
#include <vector>

TEST_CASE("Simple") {
    std::vector<int> array{1, 0, 0, 2, 0, 3, 0};
    FilterArray(array);
    CHECK(array == std::vector<int>{1, 2, 3});
}
