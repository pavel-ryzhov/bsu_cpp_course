#include "accurate_sum.h"

#include <catch2/catch_test_macros.hpp>
#include <cmath>
#include <limits>
#include <vector>

bool Equal(long double a, long double b) {
    return std::abs(a - b) < std::numeric_limits<long double>::epsilon();
}

TEST_CASE("VerySimple") {
    const std::vector<long double> data{
      0.,  1., 2., 3.,
      4.5, -6

    };
    REQUIRE(Equal(4.5, AccurateSum(data)));
}

TEST_CASE("Simple") {
    const std::vector<long double> data{
      18014398509481984.0,  // 2**54
      18014398509481982.0,  // 2**54-2
      -9007199254740991.0,  // -(2**53-1)
      -9007199254740991.0,  // -(2**53-1)
      -9007199254740991.0,  // -(2**53-1)
      -9007199254740991.0,  // -(2**53-1)

    };
    REQUIRE(Equal(2., AccurateSum(data)));
}
