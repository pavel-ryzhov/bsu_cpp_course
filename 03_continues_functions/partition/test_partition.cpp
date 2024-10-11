#include "partition.h"

#include <catch2/catch_test_macros.hpp>
#include <vector>

TEST_CASE("Simple") {
    std::vector<int> array{0, 2, -5, 4, -6, 3, 0};
    PartitionBySign(array);
    CHECK(array == std::vector<int>{-5, -6, 0, 0, 2, 4, 3});
}
