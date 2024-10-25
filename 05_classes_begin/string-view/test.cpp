#include "string_view.h"
#include "tools/util/util.h"

#include <algorithm>
#include <array>
#include <catch2/catch_test_macros.hpp>
#include <chrono>
#include <concepts>
#include <cstdint>
#include <cstdio>
#include <iostream>
#include <iterator>
#include <random>
/* #include <sanitizer/asan_interface.h>  // NOLINT */

#include <stdexcept>
#include <string>
#include <string_view>
#include <type_traits>
#include <vector>

template <class T>
concept HasConstructorFromNull = requires(T t) { requires requires { T(nullptr); }; };

template <class T>
concept HasSubStr = requires(T t) {
    { t.Substr() } -> std::same_as<T>;
};

TEST_CASE("DefaultConstructors") {
    const StringView sv;
    CHECK(sv.Data() == nullptr);
    CHECK(sv.Size() == 0);
}

TEST_CASE("Constructors") {  // NOLINT(readability-function-cognitive-complexity)
    {
        const std::string cppstr = "Foo";
        const StringView cppstr_v(cppstr);
        REQUIRE(cppstr_v.Size() == 3);
    }

    {
        char array[3] = {'B', 'a', 'r'};              // NOLINT
        StringView array_v(array, std::size(array));  // NOLINT
        REQUIRE(array_v.Size() == 3);
    }
    {
        const char* one_0_two = "One\0Two";
        const StringView one_two_v{one_0_two, 7};
        REQUIRE(one_two_v.Size() == 7);
        const StringView one_v{one_0_two};
        REQUIRE(one_v.Size() == 3);
    }
    {
        const std::array ar = {'P', 'u', 'b'};
        const StringView ar_v(ar.begin(), ar.end());
        REQUIRE(ar_v.Size() == 3);
    }
    // if you want, you can do it
    /* { */
    /*     std::array ar = {'P', 'u', 'b'}; */
    /*     StringView ar_v2{ar}; // OK in C++23 */
    /* } */
    {
        [[maybe_unused]] auto zero = [] { /* ... */ return nullptr; };
        if constexpr (HasConstructorFromNull<StringView>) {
            std::cerr << "won't compile since C++23!";
            REQUIRE(false);
        } else {
            REQUIRE(true);
        }
    }
    {
        const auto* cs = "abacaba";
        const StringView sv(cs);
        CHECK(sv[3] == 'c');
        CHECK(sv.Data() == cs);
        CHECK(sv.Size() == 7);
    }
    {
        const auto* cs = "caba";
        const StringView sv{cs, 3};
        CHECK(sv[0] == 'c');
        CHECK(sv.Data() == cs);
        CHECK(sv.Size() == 3);
    }
    {
        std::string s = "abacaba";
        const StringView sv(s);
        CHECK(sv[3] == 'c');
        CHECK(sv.Data() == s.data());
        CHECK(sv.Size() == 7);
    }
    {
        std::string s = "abacaba";
        const StringView sv{s, 3};
        CHECK(sv[1] == 'b');
        CHECK(sv.Data() == s.data());
        CHECK(sv.Size() == 3);
    }
    {
        const StringView s = "abacaba";
        const StringView sv = s.Substr(3, 3);
        CHECK(sv[1] == 'a');
        const auto* expected_data = s.Data();
        std::advance(expected_data, 3);
        CHECK(sv.Data() == expected_data);
        CHECK(sv.Size() == 3);
    }
}

TEST_CASE("operator=") {
    const StringView v = "Hello, world";
    CHECK(v.Size() == 12);
}

TEST_CASE("at") {  // NOLINT(readability-function-cognitive-complexity)
    std::string s = "Hello, world";
    const StringView v = "Hello, world";
    CHECK(v.Size() == 12);

    try {
        for (std::size_t i = 0; i < v.Size(); ++i) {
            CHECK(v.At(i) == s[i]);
        }
    } catch (const std::out_of_range& e) {
        CHECK(false);
    }
    REQUIRE_THROWS_AS(v.At(v.Size()), std::out_of_range);
    REQUIRE_THROWS_AS(v.At(-1), std::out_of_range);
}

TEST_CASE("Constness") {
    const StringView s = "abacaba";
    const StringView sv = s.Substr(2, 3);
    CHECK(sv[2] == 'a');
    const auto* expected_data = s.Data();
    std::advance(expected_data, 2);
    CHECK(sv.Data() == expected_data);
    CHECK(sv.Size() == 3);
}

TEST_CASE("Change source") {
    {
        std::string ms = "abacaba";
        const StringView s{ms};
        const StringView sv = s.Substr(4);
        ms[5] = 'd';
        CHECK(sv[1] == 'd');
        CHECK(s[1] == 'b');
    }
    {
        char cs[] = "abacaba";  // NOLINT
        auto* cs_data{cs};      // NOLINT
        std::advance(cs_data, 1);
        const StringView sv{cs_data, 3};
        cs[3] = 'f';
        CHECK(sv[2] == 'f');
    }
}

TEST_CASE("Big") {
    constexpr auto kSize = 100'000;

    RandomGenerator rnd{38'545'678};
    auto s = rnd.GenString(kSize);
    const StringView temp_s{s};
    const StringView sv = temp_s.Substr(1);

    for (auto i = 0; i < kSize; ++i) {
        auto ind = rnd.GenInt(1, kSize - 1);
        s[ind] = rnd.GenInt('a', 'z');
        REQUIRE(s[ind] == sv[ind - 1]);
    }
    REQUIRE(sv.Size() == kSize - 1);
}

TEST_CASE("My vs std!") {  // NOLINT(readability-function-cognitive-complexity)
    constexpr auto kSize = 100'000;
    auto is_equal = [](const auto& my, const auto& std_v) {
        REQUIRE(my.Size() == std_v.size());
        REQUIRE(my.Data() == std_v.data());
        REQUIRE(my.Empty() == std_v.empty());
        if (!my.Empty()) {
            REQUIRE(my.Front() == std_v.front());
            REQUIRE(my.Back() == std_v.back());
        }
    };

    RandomGenerator rnd{38'545'678};
    auto s = rnd.GenString(kSize);
    size_t iterations = 100'000;
    while (--iterations != 0U) {
        const StringView view_s{s};
        const std::string_view std_view_s{s};
        is_equal(view_s, std_view_s);
        is_equal(view_s.Substr(), std_view_s.substr());
        auto pos = rnd.GenInt(0, kSize);
        is_equal(view_s.Substr(pos), std_view_s.substr(pos));
        auto count = rnd.GenInt(0, 2 * kSize);
        is_equal(view_s.Substr(pos, count), std_view_s.substr(pos, count));
        is_equal(view_s.Substr(pos, std::string::npos), std_view_s.substr(pos, std::string::npos));
    }
}

TEST_CASE("Substr") {
    // You can see some performance, just enable flag below
    constexpr const bool kEnable = false;
    if constexpr (!kEnable) {
        return;
    }
#if defined(__has_feature)
#if (__has_feature(address_sanitizer) || defined(__SANITIZE_ADDRESS__))
    std::cout << "Disabled in asan\n";
#else
    static const int64_t kCount = 10'000;
    static const int kAccess = 100'000'000;
    std::cout << '\n';

    constexpr auto kSize = 1'000'000;
    RandomGenerator rnd{38'545'678};
    const std::string rd_str = rnd.GenString(kSize);

    const size_t size = rd_str.size();

    std::cout << "String size: " << size << "\n\n";

    // случайные значения
    std::random_device seed;
    std::mt19937 engine(seed());
    std::uniform_int_distribution<int64_t> uniform_dist(0LL, static_cast<int64_t>(size) - 1);
    std::vector<int64_t> rand_values;
    rand_values.reserve(kAccess);
    for (auto i = 0; i < kAccess; ++i) {
        rand_values.push_back(uniform_dist(engine));
    }

    auto test_one_type = [&rand_values](const std::string& name, const auto& rd_str) {
        auto start = std::chrono::steady_clock::now();
        for (auto i = 0; i < kAccess; ++i) {
            int64_t baseline_ssize{};
            int64_t ssize{};
            if constexpr (HasSubStr<std::remove_cvref_t<decltype(rd_str)> >) {
                auto temp = rd_str.Substr(rand_values[i], kCount);
                baseline_ssize = rd_str.Size();
                ssize = temp.Size();
            } else {
                auto temp = rd_str.substr(rand_values[i], kCount);
                baseline_ssize = std::ssize(rd_str);
                ssize = std::ssize(temp);
            }
            REQUIRE(
                ssize ==
                std::max(
                    static_cast<int64_t>(0), std::min(baseline_ssize - rand_values[i], kCount)));
        }
        const std::chrono::duration<double> dur_string = std::chrono::steady_clock::now() - start;
        std::cout << name << dur_string.count() << " seconds" << '\n';
    };
    test_one_type("std::string::substr:      ", rd_str);

    const std::string_view rd_str_view{rd_str.c_str(), size};
    test_one_type("std::string_view::substr: ", rd_str_view);
    static_assert(HasSubStr<StringView>);
    const StringView my_rd_str_view{rd_str.c_str(), size};
    test_one_type("StringView::substr:       ", my_rd_str_view);

    std::cout << '\n';
#endif
#endif
}
