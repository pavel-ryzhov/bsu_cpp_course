// #include "98_raytracer/raytracer-geom/sphere.h"
//  #include "98_raytracer/raytracer-geom/geometry.h"
 #include "98_raytracer/raytracer-geom/vector.h"
//  #include "98_raytracer/raytracer-geom/triangle.h"

// #include "98_raytracer/raytracer-geom/ray.h"
// #include "98_raytracer/raytracer-reader/scene.h"
#include <array>
#include <concepts>
#include <cstdint>
#include <filesystem>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <optional>
#include <cstddef>
#include <type_traits>
#include <utility>
#include <vector>

static void REQUIRE(bool expr) {
    std::cout << expr << std::endl;
}

static void REQUIRE_FALSE(bool expr) {
    REQUIRE(!expr);
}

constexpr auto kX = 12.3;
constexpr auto kY = 45.6;
constexpr auto kZ = 78.9;

#include <cmath>

// void CalculateBasis(const Vector& new_k) {
//     const Vector i{1, 0, 0};
//     const Vector j{0, 1, 0};
//     const Vector k{0, 0, 1};
//     // const auto new_i = CrossProduct(new_k, k);
//     // const auto new_j = CrossProduct(new_k, new_i);
//     const auto new_i = CrossProduct(new_k, k);
//     const auto new_j = CrossProduct(new_k, new_i);
//     std::cout << new_i << std::endl;
//     std::cout << new_j << std::endl;
//     std::cout << new_k << std::endl;
// }


static std::array<Vector, 3> CalculateBasis(Vector new_k) {
    new_k.Normalize();
    auto new_j = CrossProduct(new_k, {1, 0, 0});
    auto new_i = CrossProduct(new_j, new_k);
    if (std::abs(new_i.Length()) < kEpsilon) [[unlikely]] {
        new_i = CrossProduct({0, 1, 0}, new_k);
        new_j = CrossProduct(new_k, new_i);
    }
    std::cout << new_i << std::endl;
    std::cout << new_j << std::endl;
    std::cout << new_k << std::endl;
    return {new_i, new_j, new_k};
}

static Vector TranslateCoords(const std::array<const Vector, 3>& basis, const Vector& r0, const Vector& coords) {
    const auto x = DotProduct(coords, {basis[0][0], basis[1][0], basis[2][0]}) + r0[0];
    const auto y = DotProduct(coords, {basis[0][1], basis[1][1], basis[2][1]}) + r0[1];
    const auto z = DotProduct(coords, {basis[0][2], basis[1][2], basis[2][2]}) + r0[2];
    return {x, y, z};
}

template <class T, class... U>
concept any_of = std::disjunction_v<std::is_same<T, U>...>;

template<class T>
requires any_of<T, int, int16_t>
T Sum(T a, T b) {
    return  a + b;;
}

int main() {
    std::string str;
    std::cout << (std::cin >> str);
}