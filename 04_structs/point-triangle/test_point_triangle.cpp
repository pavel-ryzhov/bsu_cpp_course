#include "point_triangle.h"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("Your test") {
    IsPointInTriangle(Triangle{Point{0, 0}, Point{0, 0}, Point{0, 0}}, Point{0, 0});
}
