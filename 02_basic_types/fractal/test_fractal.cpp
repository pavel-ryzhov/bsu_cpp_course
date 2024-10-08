#include "fractal.h"

#include <catch2/catch_message.hpp>
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Compare") {
    for (int i = 1; i < 50; ++i) {
        INFO("i == " << i);
        REQUIRE(GenerateAsFunction(i) == GenerateAsSequence(i));
    }
}
