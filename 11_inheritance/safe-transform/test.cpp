#include "safe_transform.h"

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers.hpp>
#include <catch2/matchers/catch_matchers_range_equals.hpp>
#include <catch2/matchers/catch_matchers_vector.hpp>
#include <cctype>
#include <deque>
#include <exception>
#include <forward_list>
#include <ranges>
#include <stdexcept>
#include <string>
#include <vector>

using Catch::Matchers::Equals;
using Catch::Matchers::RangeEquals;

TEST_CASE("Transform works 1") {
    std::vector data = {1, 2, 3, 4};
    TransformIf(data.begin(), data.end(), [](int x) { return x % 2 == 0; }, [](int& x) { x *= x; });
    CHECK_THAT(data, Equals(std::vector{1, 4, 3, 16}));
}

TEST_CASE("Transform works 2") {
    std::string s = "abacaba";
    TransformIf(
        s.begin(), s.end(), [](char) { return true; },
        [](char& c) { c = static_cast<char>(std::toupper(c)); });
    CHECK(s == "ABACABA");
}

TEST_CASE("Transform works 3") {
    std::vector data = {1, 2, 0, 5, 42};
    TransformIf(data.begin(), data.end(), [](int x) { return x != 0; }, [](int& x) { x = 42 / x; });
    CHECK_THAT(data, Equals(std::vector{42, 21, 0, 8, 1}));
}

TEST_CASE("Predicate throws") {  // NOLINT(readability-function-cognitive-complexity)
    {
        std::vector<std::string> data = {"aba", "caba"};
        auto expected = data;
        REQUIRE_THROWS_AS(
            TransformIf(
                data.begin(), data.end(),
                [](const std::string& cur) {
                    if (cur.size() == 4) {
                        throw std::runtime_error{"Don't do this"};
                    }
                    return true;
                },
                [](std::string& cur) { cur.erase(0, 1); }),
            std::runtime_error);
        CHECK_THAT(data, Equals(expected));
    }

    {
        std::forward_list vals = {-5., -3., 1., -4.};
        auto expected = vals;
        REQUIRE_THROWS_AS(
            TransformIf(
                vals.begin(), vals.end(),
                [](double x) {
                    if (x > 0) {
                        throw std::runtime_error{"Positive value"};
                    }
                    return true;
                },
                [](double& x) { x = -x; }),
            std::runtime_error);
        CHECK_THAT(vals, RangeEquals(expected));
    }
}

TEST_CASE("Functor throws") {
    std::vector<std::string> data = {"a", "b", "caba", "hello", "TEST"};
    auto expected = data;
    REQUIRE_THROWS_AS(
        TransformIf(
            data.begin(), data.end(), [](const std::string& s) { return s.size() > 2; },
            [](std::string& s) {
                s[2] = std::toupper(s[2]);
                if (s.size() == 5) {
                    throw std::invalid_argument{""};
                }
            }),
        std::invalid_argument);
    CHECK_THAT(data, Equals(expected));
}

struct Int {
    int x;  // NOLINT(misc-non-private-member-variables-in-classes)

    Int(Int&&) = default;
    Int& operator=(Int&&) = default;
    ~Int() = default;

    Int(int x) : x{x} {  // NOLINT
    }

    Int(const Int& other) : x(other.x) {
        UpdateCounter();
    }

    Int& operator=(const Int& other) {
        if (this == &other) {
            return *this;
        }
        UpdateCounter();
        x = other.x;
        return *this;
    }

    static inline int counter;    // NOLINT
    static inline int max_value;  // NOLINT

    static void Reset(int max_val) {
        counter = 0;
        max_value = max_val;
    }

    static void UpdateCounter() {
        if (++counter >= max_value) {
            throw std::logic_error{"Fail"};
        }
    }

    bool operator==(const Int&) const = default;
};

TEST_CASE("Copy fails") {
    Int::Reset(100);
    std::vector<Int> data = {1, 2, 3, 4, 5};
    Int::Reset(3);
    TransformIf(
        data.begin(), data.end(), [](const Int&) { return true; },
        [](Int& val) { val.x *= val.x; });
    REQUIRE(Int::counter >= Int::max_value);
    for (auto i : std::views::iota(0UL, data.size())) {
        REQUIRE(data[i].x == static_cast<int>((i + 1) * (i + 1)));
    }
}

TEST_CASE("All fails") {
    Int::Reset(100);
    std::forward_list<Int> data = {3, 5, 2};
    Int::Reset(2);
    REQUIRE_THROWS_AS(
        TransformIf(
            data.begin(), data.end(), [](const Int&) { return true; },
            [](Int& val) {
                val.x *= 2;
                if (val.x == 10) {
                    throw std::range_error{"Too big"};
                }
            }),
        std::exception);
    CHECK(Int::counter >= Int::max_value);
}

TEST_CASE("Copy predicate only") {
    Int::Reset(100);
    std::deque<Int> data = {1, 1, 1, 1, 1, 2, 3};
    auto expected = data;
    Int::Reset(3);
    REQUIRE_THROWS_AS(
        TransformIf(
            data.begin(), data.end(),
            [](const Int& val) {
                if (val.x == 3) {
                    throw std::runtime_error{""};
                }
                return val.x == 2;
            },
            [](Int& val) { val.x += 2; }),
        std::runtime_error);
    CHECK(Int::counter < Int::max_value);
    CHECK_THAT(data, RangeEquals(expected));
}

TEST_CASE("Stress") {  // NOLINT(readability-function-cognitive-complexity)
    constexpr auto kMaxCount = 100;

    std::deque<Int> data;
    for (auto i : std::views::iota(0, 1'000'000)) {
        data.emplace_back(i);
    }

    auto predicate = [](const Int& val) { return val.x % 2 == 0; };
    for (auto i = 0; i < 10'000; ++i) {
        Int::Reset(100'500);
        REQUIRE_THROWS_AS(
            TransformIf(
                data.begin(), data.end(), predicate,
                [](Int& val) {
                    if (val.x++ == kMaxCount) {
                        throw std::runtime_error{"Stop"};
                    }
                }),
            std::runtime_error);
        for (auto j : std::views::iota(0, kMaxCount)) {
            REQUIRE(data[j].x == j);
        }
    }
}

struct Unstable {
    explicit Unstable(int x) : x{x} {
    }

    Unstable(const Unstable& other) : x{GetValue(other)} {
    }

    Unstable& operator=(const Unstable& other) {
        if (this == &other) {
            return *this;
        }
        x = GetValue(other);
        return *this;
    }

    Unstable(Unstable&&) = default;
    Unstable& operator=(Unstable&&) = default;
    ~Unstable() = default;

    bool operator==(const Unstable&) const = default;

    static inline bool enabled;  // NOLINT
    int x;                       // NOLINT

   private:
    static int GetValue(const Unstable& other) {
        if (enabled) {
            flag = !flag;
            if (flag) {
                throw std::overflow_error{"Some exception"};
            }
        }
        return other.x;
    }

    static inline bool flag;  // NOLINT
};

TEST_CASE("Unstable") {
    constexpr auto kPredicate = [](const Unstable& element) { return element.x % 3; };

    std::vector<Unstable> v;
    std::vector<Unstable> expected;
    for (auto i : std::views::iota(0, 50'000)) {
        auto& element = v.emplace_back(i);
        expected.emplace_back(kPredicate(element) != 0 ? i + 5 : i);
    }
    Unstable::enabled = true;
    TransformIf(v.begin(), v.end(), kPredicate, [kPredicate](Unstable& element) {
        if (kPredicate(element) == 0) {
            FAIL("Wrong element");
        }
        element.x += 5;
    });
    CHECK_THAT(v, Equals(expected));
}
