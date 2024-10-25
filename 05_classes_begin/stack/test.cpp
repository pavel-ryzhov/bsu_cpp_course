#include "stack.h"

#include <catch2/catch_test_macros.hpp>
#include <cstdio>
#include <ranges>

TEST_CASE("Simple") {
    Stack s;
    s.Push(0);
    REQUIRE(s.Top() == 0);
    s.Push(1);
    REQUIRE(s.Top() == 1);
    s.Push(2);
    REQUIRE(s.Top() == 2);

    REQUIRE(s.Pop());
    REQUIRE(s.Top() == 1);
    REQUIRE(s.Pop());
    REQUIRE(s.Top() == 0);
    REQUIRE(s.Pop());
    REQUIRE_FALSE(s.Pop());
}

TEST_CASE("Empty") {
    Stack s;
    REQUIRE(s.Empty());
    REQUIRE(s.Size() == 0);

    s.Push(1);
    REQUIRE_FALSE(s.Empty());
    REQUIRE(s.Size() == 1);
    REQUIRE(s.Pop());
}

TEST_CASE("Long!") {  // NOLINT(readability-function-cognitive-complexity)
    {
        constexpr auto kRange = std::views::iota(0, 100'000);

        Stack s;
        for (auto i : kRange) {
            REQUIRE(s.Size() == static_cast<size_t>(i));
            s.Push(i);
            REQUIRE(s.Top() == i);
        }
        REQUIRE(s.Size() == kRange.size());

        for (auto i : std::views::reverse(kRange)) {
            REQUIRE(s.Top() == i);
            REQUIRE(s.Pop());
            REQUIRE(s.Size() == static_cast<size_t>(i));
        }
        REQUIRE(s.Empty());
        REQUIRE(s.Size() == 0);
    }

    {
        constexpr auto kRange = std::views::iota(0, 1'000'000);

        Stack s;
        for (auto i : kRange) {
            REQUIRE(s.Size() == static_cast<size_t>(i));
            s.Push(i);
            REQUIRE(s.Top() == i);
        }
        REQUIRE(s.Size() == kRange.size());

        auto ans_top = s.Top();
        for (auto _ [[maybe_unused]] : kRange) {
            REQUIRE(s.Top() == ans_top);
            REQUIRE(s.Pop());
            s.Push(ans_top);
            REQUIRE(s.Size() == kRange.size());
        }
    }
}
