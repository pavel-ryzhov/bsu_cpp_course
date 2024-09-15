#include "sum.h"

#include <cstdint>
#include <gtest/gtest.h>
#include <type_traits>

TEST(Public, Simple) {
    EXPECT_EQ(Sum(2, 3), 5);
}

TEST(Public, Signature) {
    static_assert(
        std::is_same_v<decltype(&Sum), int64_t (*)(int32_t, int32_t)>, "Wrong signature!");
}
