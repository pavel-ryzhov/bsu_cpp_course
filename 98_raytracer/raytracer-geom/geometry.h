#pragma once

#include "98_raytracer/raytracer-geom/intersection.h"
#include "98_raytracer/raytracer-geom/ray.h"
#include "98_raytracer/raytracer-geom/sphere.h"
#include "98_raytracer/raytracer-geom/triangle.h"
#include "98_raytracer/raytracer-geom/vector.h"
#include "98_raytracer/raytracer-reader/object.h"

#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <optional>
#include <variant>

template<sphere T>
std::optional<Intersection> GetIntersection(const Ray& ray, const T& sph) {
    const Sphere sphere = [&sph] {
        if constexpr (std::is_same_v<T, SphereObject>) {
            return sph.GetInner();
        } else {
            return sph;
        }
    }(); 
    const Vector r = ray.GetOrigin() - sphere.GetCenter();
    const double a = std::pow(ray.GetDirection().Length(), 2);
    const double b = 2 * DotProduct(ray.GetDirection(), r);
    const double c = std::pow(r.Length(), 2) - std::pow(sphere.GetRadius(), 2);
    const double d = std::pow(b, 2) - 4 * a * c;
    double t = 0;
    bool is_inside = false;
    if (std::abs(d) < kEpsilon) [[unlikely]] {
        t = .5 * -b / a;
    } else {
        if (d < -kEpsilon) {
            return std::nullopt;
        }
        const double t1 = .5 / a * (-b + std::sqrt(d));
        const double t2 = .5 / a * (-b - std::sqrt(d));
        if (t1 < -kEpsilon && t2 < -kEpsilon) {
            return std::nullopt;
        }
        is_inside = t1 < -kEpsilon || t2 < -kEpsilon;
        t = is_inside ? std::max(t1, t2) : std::min(t1, t2);
    }
    const Vector position = ray.GetOrigin() + ray.GetDirection() * t;
    Vector normal = position - sphere.GetCenter();
    if (is_inside) {
        normal *= -1;
    }
    normal.Normalize();
    return Intersection{position, normal, (position - ray.GetOrigin()).Length(), is_inside};
}

inline Vector Reflect(const Vector& ray, const Vector& normal) {
    return ray - 2 * DotProduct(ray, normal) * normal;
}

inline std::optional<Vector> Refract(const Vector& ray, const Vector& normal, double eta) {
    const double c = -DotProduct(normal, ray);
    const double t = 1 - std::pow(eta, 2) * (1 - std::pow(c, 2));
    if (t < -kEpsilon) {
        return std::nullopt;
    }
    return eta * ray + (eta * c - std::sqrt(t)) * normal;
}

inline Vector GetBarycentricCoords(const Triangle& triangle, const Vector& point) {
    const double area = triangle.Area();
    const Triangle tr1{triangle[0], triangle[2], point};
    const Triangle tr2{triangle[0], triangle[1], point};
    const double u = tr1.Area() / area;
    const double v = tr2.Area() / area;
    return {1 - u - v, u, v};
}

inline Vector GetInterpolatedNormal(const TriangleObject& triangle, const Vector& position) {
    const auto baricentric_coords = GetBarycentricCoords(triangle.GetInner(), position);
    return {baricentric_coords[0] * *triangle.GetNormal<0>() + baricentric_coords[1] * *triangle.GetNormal<1>() + baricentric_coords[2] * *triangle.GetNormal<2>(), std::monostate()};
}

template<triangle T>
std::optional<Intersection> GetIntersection(const Ray& ray, const T& tr) {
    const Triangle triangle = [&tr] {
        if constexpr (std::is_same_v<T, TriangleObject>) {
            return tr.GetInner();
        } else {
            return tr;
        }
    }();
    const Vector edge1 = triangle[1] - triangle[0];
    const Vector edge2 = triangle[2] - triangle[0];
    const Vector ray_cross_edge2 = CrossProduct(ray.GetDirection(), edge2);
    const double det = DotProduct(edge1, ray_cross_edge2);
    if (std::abs(det) < kEpsilon) {
        return std::nullopt;
    }
    const double inv_det = 1. / det;
    const Vector s = ray.GetOrigin() - triangle[0];
    const double u = inv_det * DotProduct(s, ray_cross_edge2);
    if (u < -kEpsilon || u - 1 > kEpsilon) {
        return std::nullopt;
    }
    const Vector s_cross_edge1 = CrossProduct(s, edge1);
    const double v = inv_det * DotProduct(ray.GetDirection(), s_cross_edge1);
    if (v < -kEpsilon || u + v - 1 > kEpsilon) {
        return std::nullopt;
    }
    const double t = inv_det * DotProduct(edge2, s_cross_edge1);
    if (t > kEpsilon) {
        const Vector position = ray.GetOrigin() + ray.GetDirection() * t;
        const Vector normal = [&] {
            if constexpr (std::is_same_v<T, TriangleObject>) {
                if (tr.HasNormals()) {
                    return GetInterpolatedNormal(tr, position);
                }
            }
            Vector normal = CrossProduct(edge1, edge2);
            normal.Normalize();
            if (DotProduct(normal, ray.GetDirection()) > kEpsilon) {
                normal *= -1;
            }
            return normal;
        }();
        return Intersection{position, normal, (position - ray.GetOrigin()).Length()};
    }
    return std::nullopt;
}