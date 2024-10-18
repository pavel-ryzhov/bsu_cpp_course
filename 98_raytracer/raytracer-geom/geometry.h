#pragma once

#include "98_raytracer/raytracer-geom/intersection.h"
#include "98_raytracer/raytracer-geom/ray.h"
#include "98_raytracer/raytracer-geom/sphere.h"
#include "98_raytracer/raytracer-geom/triangle.h"
#include "98_raytracer/raytracer-geom/vector.h"

#include <optional>

inline std::optional<Intersection> GetIntersection(const Ray& ray, const Sphere& sphere);

inline std::optional<Intersection> GetIntersection(const Ray& ray, const Triangle& triangle);

inline Vector Reflect(const Vector& ray, const Vector& normal);

inline std::optional<Vector> Refract(const Vector& ray, const Vector& normal, double eta);

inline Vector GetBarycentricCoords(const Triangle& triangle, const Vector& point);
