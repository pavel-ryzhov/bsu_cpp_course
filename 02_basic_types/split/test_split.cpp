#include "split.h"

#include <catch2/catch_test_macros.hpp>
#include <string>
#include <vector>

TEST_CASE("Simple") {
    {
        const std::vector<std::string> expected{"aba", "caba", "1"};
        REQUIRE(expected == Split("aba caba 1", " "));
    }
    {
        const std::vector<std::string> expected{"aba"};
        REQUIRE(expected == Split("aba", " "));
    }
}

TEST_CASE("Empty") {
    REQUIRE(Split("", " ").empty());
}

TEST_CASE("Full match") {
    const std::vector<std::string> expected{"", ""};
    REQUIRE(expected == Split("full match", "full match"));
}

TEST_CASE("Some tests") {
    {
        const std::vector<std::string> expected{"just", "", "a", "test", ""};
        REQUIRE(expected == Split("just  a test ", " "));
    }
    {
        const std::vector<std::string> expected{"hello", "world,no split here", "", "1", ""};
        REQUIRE(expected == Split("hello, world,no split here, , 1, ", ", "));
    }
    {
        const std::vector<std::string> expected{"", "a", "b c", "def", "g h "};
        REQUIRE(expected == Split("  a  b c  def  g h ", "  "));
    }
}
