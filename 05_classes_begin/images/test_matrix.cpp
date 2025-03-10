#include "matrix.h"

#include <catch2/catch_test_macros.hpp>
#include <cstddef>
#include <exception>
#include <ostream>
#include <vector>

using IMatrix = Matrix<int>;
using IVector = std::vector<std::vector<int>>;

template <class T>
inline std::ostream& operator<<(std::ostream& os, const Matrix<T>& matrix) {
    os << "{";
    for (size_t i = 0; i < matrix.Rows(); ++i) {
        os << (i > 0 ? "," : "") << "{";
        for (size_t j = 0; j < matrix.Columns(); ++j) {
            os << (j > 0 ? "," : "") << matrix(i, j);
        }
        os << "}";
    }
    os << "}";
    return os;
}

//
TEST_CASE("Constructor") {
    const IMatrix a(2, 3);
    const IMatrix b(2, 3, 1);
    const IMatrix c(a.Data());
    const IMatrix d(3);
    const IMatrix e({{1, 2}, {3, 4}, {5, 6}});

    CHECK(a.Data() == IVector{{0, 0, 0}, {0, 0, 0}});
    CHECK(b.Data() == IVector{{1, 1, 1}, {1, 1, 1}});
    CHECK(c.Data() == IVector{{0, 0, 0}, {0, 0, 0}});
    CHECK(d.Data() == IVector{{0, 0, 0}, {0, 0, 0}, {0, 0, 0}});
    CHECK(e.Data() == IVector{{1, 2}, {3, 4}, {5, 6}});

    CHECK_THROWS_AS(IMatrix(IVector{{0, 1, 2}, {0, 0}}), std::exception);
    CHECK_THROWS_AS(IMatrix(IVector{}), std::exception);
}

//
TEST_CASE("Copy constructor") {
    IMatrix a(1, 2);
    const IMatrix b(a);
    const IMatrix c = a;
    a(0, 0) = 1;

    CHECK(a.Data() == IVector{{1, 0}});
    CHECK(b.Data() == IVector{{0, 0}});
    CHECK(c.Data() == IVector{{0, 0}});
}

//
TEST_CASE("Accessors") {
    {
        IMatrix a(IVector{{1, 2}});
        CHECK(a.Rows() == 1);
        CHECK(a.Columns() == 2);
        CHECK(a(0, 0) == 1);
        CHECK(a(0, 1) == 2);
        CHECK_THROWS_AS(a(1, 1), std::exception);
        a(0, 0) = 0;
        CHECK(a.Data() == IVector{{0, 2}});
    }
    {
        const IMatrix a(1, 1);
        CHECK(a(0, 0) == 0);
    }
    {
        const IMatrix a(3, 5);
        CHECK(3U == a.Rows());
        CHECK(5U == a.Columns());
    }
}

//
TEST_CASE("Constness") {
    {
        const IMatrix a({{1, 2}, {3, 4}});
        const auto& b = a;
        CHECK(2U == b.Rows());
        CHECK(2U == b.Columns());
        CHECK(2 == b(0, 1));
    }
    {
        const auto first = IMatrix::Identity(3);
        const IMatrix second(3);
        CHECK(first == Transpose(first));
        CHECK(second == first - first);
        CHECK(first == first * first);
    }
}

//
TEST_CASE("Transpose") {
    const IMatrix a({{0, 1}, {2, 3}, {4, 5}});
    CHECK(a.Transpose().Data() == IVector{{0, 2, 4}, {1, 3, 5}});
    CHECK(Transpose(a).Data() == a.Transpose().Data());
}

//
TEST_CASE("Operators") {
    using FMatrix = Matrix<double>;

    FMatrix a({{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}});
    const FMatrix b({{0.0, 1.0, 0.0}, {1.0, 1.0, 2.0}});
    const FMatrix c({{-1.0, -1.0}, {1.0, 1.0}, {1.0, -1.0}});

    CHECK(a != Transpose(a));
    CHECK(Transpose(a) == FMatrix({{1.0, 4.0}, {2.0, 5.0}, {3.0, 6.0}}));

    auto old_a = a;
    CHECK((a += b) == FMatrix({{1.0, 3.0, 3.0}, {5.0, 6.0, 8.0}}));
    CHECK((a -= b) == old_a);
    CHECK((a -= a) == FMatrix(2, 3));

    CHECK((b * c) == FMatrix({{1.0, 1.0}, {2.0, -2.0}}));
}

//
TEST_CASE("Big") {
    const auto a = IMatrix::Identity(300);
    CHECK(a * a == a);
}
