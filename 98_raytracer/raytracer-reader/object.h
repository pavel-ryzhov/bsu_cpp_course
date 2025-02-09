#pragma once

#include "98_raytracer/raytracer-geom/sphere.h"
#include "98_raytracer/raytracer-geom/triangle.h"
#include "98_raytracer/raytracer-geom/vector.h"
#include "98_raytracer/raytracer-reader/material.h"

#include <array>
#include <cstddef>
#include <optional>

struct TriangleObject {

    TriangleObject(const Material* material, const Triangle& triangle, std::optional<const std::array<Vector, 3>>& normals) : material_(material), polygon_(triangle), normals_(normals) {}


    template <size_t Ind>
    [[nodiscard]] const Vector* GetNormal() const {
        return normals_ ? &(*normals_)[Ind] : nullptr;
    }

    [[nodiscard]] const auto& GetInner() const noexcept {
        return polygon_;
    }

    [[nodiscard]] const auto* GetMaterialPtr() const noexcept {
        return material_;
    }

    [[nodiscard]] bool HasNormals() const {
        return normals_.has_value();
    }

   private:
    const Material* material_ = nullptr;
    Triangle polygon_;
    std::optional<std::array<Vector, 3>> normals_;
};


struct SphereObject {
    SphereObject(const Material* material, const Vector& center, double r)
        : material_(material), sphere_(center, r) {
    }

    [[nodiscard]] const auto& GetInner() const noexcept {
        return sphere_;
    }

    [[nodiscard]] const auto* GetMaterialPtr() const noexcept {
        return material_;
    }

   private:
    const Material* material_ = nullptr;
    Sphere sphere_;
};

template<class T, class... U>
concept any_of = std::disjunction_v<std::is_same<T, U>...>;

template<class T>
concept triangle = any_of<T, TriangleObject, Triangle>;

template<class T>
concept sphere = any_of<T, SphereObject, Sphere>;

template<class T>
concept object = triangle<T> || sphere<T>;

template<class T>
concept material_object = any_of<T, SphereObject, TriangleObject>;