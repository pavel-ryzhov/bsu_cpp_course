#include "deque.h"

#include <algorithm>
#include <catch2/catch_test_macros.hpp>
#include <cstddef>
#include <deque>
#include <functional>
#include <iterator>
#include <random>
#include <ranges>
#include <unordered_set>
#include <utility>
#include <vector>

void Check(const Deque& actual, const std::vector<int>& expected) {
    REQUIRE(actual.Size() == expected.size());
    for (auto i : std::views::iota(size_t{0}, expected.size())) {
        if (actual[i] != expected[i]) {
            FAIL(i << "   " << actual[i] << " != " << expected[i]);
        }
    }
}

void CheckEq(const Deque& a, const Deque& b) {
    REQUIRE(a.Size() == b.Size());
    for (auto i : std::views::iota(size_t{0}, a.Size())) {
        if (a[i] != b[i]) {
            FAIL(a[i] << " != " << b[i]);
        }
    }
}

TEST_CASE("Deque has constructors") {
    {
        const Deque a;
        REQUIRE(a.Size() == 0);
    }
    {
        const Deque a = {1, 2, 3, 4};
        Check(a, {1, 2, 3, 4});
    }
    {
        const Deque a(5);
        Check(a, std::vector<int>(5));
    }
}

TEST_CASE("Basic methods") {
    Deque a = {1, 3, 5};
    Check(a, {1, 3, 5});

    a.PopBack();
    Check(a, {1, 3});
    a.PopFront();
    Check(a, {3});
    a.PushFront(5);
    Check(a, {5, 3});
    a.PushBack(1);
    Check(a, {5, 3, 1});

    a.Clear();
    Check(a, {});

    a.PushBack(3);
    Deque b{2, 4};
    a.Swap(b);
    Check(a, {2, 4});
    Check(b, {3});
}

TEST_CASE("Modifications with []") {
    Deque a = {9, 1, 1};
    a[0] = 1;
    a[1] = 2;
    a[2] = 3;
    Check(a, {1, 2, 3});
}

TEST_CASE("Memory layout") {
    const Deque a(129);
    for (auto i : std::views::iota(0, 127)) {
        REQUIRE(std::next(&a[i]) == &a[i + 1]);
    }
}

namespace {

#if defined(ADDRESS_SANITIZER) || defined(__SANITIZE_ADDRESS__)
constexpr inline const int kMaxValue = 100'000;
#else
constexpr inline const int kMaxValue = 1'000'000;
#endif

}  // namespace

TEST_CASE("Reallocations") {
    constexpr auto kRange = std::views::iota(0, kMaxValue);

    std::mt19937 gen{9354};  // NOLINT(cert-msc32-c,cert-msc51-cpp)
    std::bernoulli_distribution dist;
    Deque a;
    std::deque<int*> addr;

    for (auto i : kRange) {
        if (dist(gen)) {
            a.PushBack(i);
            addr.push_back(&a[a.Size() - 1]);
        } else {
            a.PushFront(i);
            addr.push_front(&a[0]);
        }
    }

    for (auto i : kRange) {
        REQUIRE(&a[i] == addr[i]);
    }
}

TEST_CASE("Copy correctness") {
    Deque a;
    auto b = a;
    b.PushBack(1);
    Check(a, {});
    Check(b, {1});

    const auto& r = b;
    b = r;
    Check(b, {1});
    a = b;
    Check(a, {1});
    a.PushFront(3);
    a.PushFront(-3);
    a.PushBack(4);

    b = std::move(a);
    Check(b, {-3, 3, 1, 4});

    auto c = std::move(b);
    Check(c, {-3, 3, 1, 4});

    Deque d = {3, 4, 5};
    auto e = d;
    Check(e, {3, 4, 5});
    d.Swap(c);
    Check(e, {3, 4, 5});
    Check(d, {-3, 3, 1, 4});
    Check(c, {3, 4, 5});
}

TEST_CASE("Move speed") {
    constexpr auto kSize = kMaxValue;

    Deque a;
    Deque b;
    for (auto i = 0; i < kSize; ++i) {
        a.PushBack(i);
        if ((i % 2) != 0) {
            b.PushBack(i);
        }
    }

    for (auto i = 0; i < 100'001; ++i) {
        std::swap(a, b);
    }
    CHECK(a.Size() == kSize / 2);
    CHECK(b.Size() == kSize);
}

TEST_CASE("Stress") {           // NOLINT(readability-function-cognitive-complexity)
    constexpr auto kNumIterations = kMaxValue;

    std::mt19937 gen{735'675};  // NOLINT(cert-msc32-c,cert-msc51-cpp)
    std::uniform_int_distribution dist{1, 10};
    Deque a;
    std::deque<int> b;
    std::deque<int*> p;
    for (auto i : std::views::iota(0, kNumIterations)) {
        if (dist(gen) > 1) {
            a.PushFront(i);
            b.push_front(i);
            p.push_front(&a[0]);
        } else {
            a.PushBack(i);
            b.push_back(i);
            p.push_back(&a[i]);
        }
    }

    for (auto i = 0; i < kNumIterations; ++i) {
        auto code = dist(gen);
        auto value = static_cast<int>(gen());
        if (code == 1) {
            a.PushFront(value);
            b.push_front(value);
            p.push_front(&a[0]);
        } else if (code == 2) {
            a.PushBack(value);
            b.push_back(value);
            p.push_back(&a[a.Size() - 1]);
        } else if (code < 6) {
            a.PopFront();
            b.pop_front();
            p.pop_front();
        } else if (code < 9) {
            a.PopBack();
            b.pop_back();
            p.pop_back();
        } else {
            auto index = value % a.Size();
            REQUIRE(a[index] == b[index]);
            REQUIRE(&a[index] == p[index]);
        }
        REQUIRE(a.Size() == b.size());
        if (i % (kNumIterations / 10) == 0) {
            auto c = a;
            auto d = std::move(a);
            a = c;
            c = std::move(d);
            std::swap(a, c);
            CheckEq(a, c);
        }
    }
    Check(a, {b.begin(), b.end()});
    REQUIRE(a.Size() == p.size());
    for (size_t i = 0; i < a.Size(); ++i) {
        CHECK(&a[i] == p[i]);
    }
}

void CheckEmptyCorrectness(void (Deque::*push)(int), void (Deque::*pop)()) {
    constexpr auto kTestSize = kMaxValue;

    Deque a;  // NOLINT(misc-const-correctness)
    for (auto i = 0; i < kTestSize; ++i) {
        (a.*push)(i);
    }
    for (auto i = 0; i < kTestSize; ++i) {
        (a.*pop)();
    }
    Check(a, {});
}

TEST_CASE("Empty correctness") {
    // There are some ways to make deque empty
    // We should test them all
    // In some ways we can cause memory leak
    CheckEmptyCorrectness(&Deque::PushBack, &Deque::PopBack);
    CheckEmptyCorrectness(&Deque::PushBack, &Deque::PopFront);
    CheckEmptyCorrectness(&Deque::PushFront, &Deque::PopBack);
    CheckEmptyCorrectness(&Deque::PushFront, &Deque::PopFront);
}

TEST_CASE("Fast self-assignment") {
    constexpr auto kRange = std::views::iota(0, kMaxValue);

    Deque a;
    auto& r = a;
    for (auto i : kRange) {
        a.PushBack(i);
        a = r;
    }
    Check(a, {kRange.begin(), kRange.end()});
}

template <typename T>
void HashCombine(std::size_t& seed, const T& key) {
    const std::hash<T> hasher;
    seed ^= hasher(key) + 0x9e37'79b9 + (seed << 6U) + (seed >> 2U);
}

namespace std {
template <typename T1, typename T2>
struct hash<std::pair<T1, T2>> {  // NOLINT(cert-dcl58-cpp)

    std::size_t operator()(const std::pair<T1, T2>& p) const noexcept {
        std::size_t seed1(0);
        HashCombine(seed1, p.first);
        HashCombine(seed1, p.second);
        std::size_t seed2(0);
        HashCombine(seed2, p.second);
        HashCombine(seed2, p.first);
        return std::min(seed1, seed2);
    }
};
}  // namespace std

TEST_CASE("Fast push front") {  // NOLINT(readability-function-cognitive-complexity)
    constexpr const int kToMax = 100'000;
    constexpr auto kRange = std::views::iota(0, kToMax);
    std::unordered_set<std::pair<size_t, int*>> index_and_ptr;

    Deque a;
    auto& r = a;
    auto check_consistences_ptr = [&]() {
        for (const auto& [k, old_ptr] : index_and_ptr) {
            REQUIRE(a.Size() >= k);
            REQUIRE(&a[a.Size() - k] == old_ptr);
        }
    };

    a.PushFront(kToMax - 1);
    int* address_last = &a[0];
    REQUIRE(address_last == &(a[0]));
    for (auto i : std::views::reverse(kRange) | std::views::drop(1)) {
        a.PushFront(i);
        a = r;
        if (i % 100'000 == 0) {
            index_and_ptr.emplace(a.Size(), &a[0]);
            check_consistences_ptr();
        }
    }
    REQUIRE(a.Size() > 0);
    REQUIRE(address_last == &(a[a.Size() - 1]));
    Check(a, {kRange.begin(), kRange.end()});
}

TEST_CASE("Ring work correct") {
    constexpr const size_t kChunkSize = 128;
    Deque ring_deque_f(kChunkSize - 1);
    int iterations = kMaxValue;
    ring_deque_f.PopBack();
    ring_deque_f.PopFront();
    Deque ring_deque_b = ring_deque_f;
    while (--iterations != 0) {
        ring_deque_f.PushFront(iterations);
        ring_deque_f.PopBack();

        ring_deque_b.PushBack(iterations);
        ring_deque_b.PopFront();
    }
    // if you implement Deque correct, Capacity must equal 2 Size. You have benefit
    constexpr const size_t kBenefit = kChunkSize;
    REQUIRE(ring_deque_f.Capacity() <= 2 * kChunkSize + kBenefit);
    REQUIRE(ring_deque_b.Capacity() <= 2 * kChunkSize + kBenefit);
}

#ifdef __linux__
#include "tools/util/util.h"

#include <cstdint>

TEST_CASE("Memory usage", "[.][no_asan]") {  // NOLINT(readability-function-cognitive-complexity)
    {
        auto before = GetMemoryUsage();
        std::vector<Deque> v(1000);
        for (auto& d : v) {
            for (auto i : std::views::iota(0, 200)) {
                d.PushBack(i);
                d.PushFront(i);
            }
        }
        CHECK(before + 10'000 > GetMemoryUsage());
    }

    Deque a(kMaxValue);
    CHECK(GetMemoryUsage() < kMaxValue / 10);

    a.Clear();
    for (auto i : std::views::iota(0, kMaxValue * 10)) {
        a.PushFront(i);
    }
    auto memory = GetMemoryUsage();
    CHECK(memory >= static_cast<int64_t>(kMaxValue / 30));
    CHECK(memory < static_cast<int64_t>(kMaxValue / 3));

    a.Clear();
    for (auto i : std::views::iota(0, kMaxValue * 80)) {
        a.PushBack(i);
    }
    memory = GetMemoryUsage();
    CHECK(memory >= static_cast<int64_t>(kMaxValue * 3));
    CHECK(memory < static_cast<int64_t>(kMaxValue * 2));
}

#endif
