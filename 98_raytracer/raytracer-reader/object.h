#pragma once

#include "98_raytracer/raytracer-geom/sphere.h"
#include "98_raytracer/raytracer-geom/triangle.h"
#include "98_raytracer/raytracer-geom/vector.h"
#include "98_raytracer/raytracer-reader/material.h"

#include <utility>
#include <vector>

struct TriangleObject {
    template <size_t Ind>
    [[nodiscard]] const Vector* GetNormal() const;

    [[nodiscard]] const auto& GetInner() const noexcept {
        return polygon_;
    }

    [[nodiscard]] const auto* GetMaterialPtr() const noexcept {
        return material_;
    }

   private:
    const Material* material_ = nullptr;
    Triangle polygon_;
    // data
};

struct SphereObject {
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
