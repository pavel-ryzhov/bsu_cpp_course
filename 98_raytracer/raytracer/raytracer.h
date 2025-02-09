#pragma once

#include "98_raytracer/raytracer-geom/geometry.h"
#include "98_raytracer/raytracer-geom/intersection.h"
#include "98_raytracer/raytracer-geom/ray.h"
#include "98_raytracer/raytracer-geom/vector.h"
#include "98_raytracer/raytracer-reader/material.h"
#include "98_raytracer/raytracer-reader/object.h"
#include "98_raytracer/raytracer-reader/scene.h"
#include "98_raytracer/raytracer/options/camera_options.h"
#include "98_raytracer/raytracer/options/render_options.h"
#include "tools/util/image.h"

#include <algorithm>
#include <array>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <filesystem>
#include <optional>
#include <utility>
#include <vector>

constexpr auto kLargeEpsilon = 1e-5;

inline std::array<Vector, 3> CalculateBasis(Vector new_k) {
    new_k.Normalize();
    auto new_i = CrossProduct({0, 1, 0}, new_k);
    auto new_j = CrossProduct(new_k, new_i);
    if (new_i.Length() < kEpsilon) [[unlikely]] {
        new_j = CrossProduct(new_k, {1, 0, 0});
        new_i = CrossProduct(new_j, new_k);
    }
    new_i.Normalize();
    new_j.Normalize();
    return {new_i, new_j, new_k};
}

inline Vector TranslateVector(
    const std::array<Vector, 3>& basis, const Vector& coords) {
    const auto x = DotProduct(coords, {basis[0][0], basis[1][0], basis[2][0]});
    const auto y = DotProduct(coords, {basis[0][1], basis[1][1], basis[2][1]});
    const auto z = DotProduct(coords, {basis[0][2], basis[1][2], basis[2][2]});
    return {x, y, z};
}

inline Vector TranslatePoint(
    const std::array<Vector, 3>& basis, const Vector& r0, const Vector& coords) {
    return TranslateVector(basis, coords) + r0;
}

inline Ray TranslateRay(const std::array<Vector, 3>& basis, const Vector& r0, const Ray& ray) {
    return {
      TranslatePoint(basis, r0, ray.GetOrigin()), TranslateVector(basis, ray.GetDirection())};
}

template <material_object T>
void FindNearestIntersection(
    std::optional<std::pair<Intersection, const Material*>>& nearest_intersection, const std::vector<T>& objects, const Ray& ray) {
    for (const auto& object : objects) {      
        if (const auto intersection = GetIntersection(ray, object); intersection && (!nearest_intersection || intersection->GetDistance() < nearest_intersection->first.GetDistance())) {
            nearest_intersection = std::make_pair(*intersection, object.GetMaterialPtr());
        }
    }
}

inline std::optional<std::pair<Intersection, const Material*>> FindNearestIntersection(const Scene& scene, const Ray& ray) {
    std::optional<std::pair<Intersection, const Material*>> intersection;
    FindNearestIntersection(intersection, scene.GetSphereObjects(), ray);
    FindNearestIntersection(intersection, scene.GetObjects(), ray);
    return intersection;
}

template<object T>
bool IsIntersecting(const std::vector<T>& objects, const Ray& ray, const Vector& ray_end) {
    return std::ranges::any_of(objects, [&ray, &ray_end](const T& object) {
        const auto intersection = GetIntersection(ray, object);
        return intersection && DotProduct(ray.GetDirection(), ray_end - intersection->GetPosition()) > kEpsilon;
    });
}

inline bool IsIntersecting(const Scene& scene, const Ray& ray, const Vector& ray_end) {
    return IsIntersecting(scene.GetSphereObjects(), ray, ray_end) || IsIntersecting(scene.GetObjects(), ray, ray_end);
}

inline Vector GetIntensity(const Scene& scene, const Intersection& intersection, const Material* material, const Ray& ray, int depth) {
    Vector sum{};
    for (const auto& light : scene.GetLights()) {
        auto to_light = light.position - intersection.GetPosition();
        to_light.Normalize();
        const Ray to_light_ray{kLargeEpsilon * to_light + intersection.GetPosition(), to_light};
        if (!IsIntersecting(scene, to_light_ray, light.position)) {
            const auto i_d = HadamardProduct(material->diffuse_color, light.intensity) * std::max(0., DotProduct(intersection.GetNormal(), to_light));
            auto from_light_reflected = Reflect(-to_light, intersection.GetNormal());
            from_light_reflected.Normalize();
            const auto i_s = HadamardProduct(material->specular_color, light.intensity) * std::pow(std::max(0., DotProduct(from_light_reflected, -ray.GetDirection())), material->specular_exponent);
            sum += i_d + i_s;
        }
    }
    sum *= material->albedo[0];
    sum += material->ambient_color + material->intensity;
    if (depth > 0) {
        if (!intersection.IsInside() && material->albedo[1] > kEpsilon) {
            auto reflected = Reflect(ray.GetDirection(), intersection.GetNormal());
            reflected.Normalize();
            const Ray ray_reflected{kLargeEpsilon * reflected + intersection.GetPosition(), reflected};
            const auto intersection_reflected_opt = FindNearestIntersection(scene, ray_reflected);
            if (intersection_reflected_opt) {
                const auto [intersection_reflected, material_reflected] = *intersection_reflected_opt;
                auto intensity_reflected = GetIntensity(scene, intersection_reflected, material_reflected, ray_reflected, depth - 1);
                sum += intensity_reflected * material->albedo[1];
            }
        }
        if (material->albedo[2] > kEpsilon) {
            const auto refracted_opt = Refract(ray.GetDirection(), intersection.GetNormal(), !intersection.IsInside() ? 1 / material->refraction_index : material->refraction_index);
            if (refracted_opt) {
                auto refracted = *refracted_opt;
                refracted.Normalize();
                const Ray ray_refracted{kLargeEpsilon * refracted + intersection.GetPosition(), refracted};
                const auto intersection_refracted_opt = FindNearestIntersection(scene, ray_refracted);
                if (intersection_refracted_opt) {
                    const auto [intersection_refracted, material_refracted] = *intersection_refracted_opt;
                    auto intensity_refracted = GetIntensity(scene, intersection_refracted, material_refracted, ray_refracted, depth - 1);
                    sum += intensity_refracted * (intersection.IsInside() ? 1. : material->albedo[2]);
                }
            }
        }
    }
    return sum;
}

inline Image Render(
    const std::filesystem::path& path, const CameraOptions& camera_options,
    const RenderOptions& render_options) {
    const auto scene = ReadScene(path);
    const auto height = 2 * std::tan(camera_options.fov / 2);
    const auto width = camera_options.screen_width * height / camera_options.screen_height;
    const auto pixel_size = width / camera_options.screen_width;
    const auto basis = CalculateBasis(camera_options.look_from - camera_options.look_to);
    std::vector<std::vector<Vector>> pixel_colors(camera_options.screen_height, std::vector<Vector>(camera_options.screen_width, Vector{}));
    double max_color = 0;
    auto get_color = [&max_color, &render_options, &scene](const std::optional<std::pair<Intersection, const Material*>>& intersection, const Ray& ray) -> Vector {
        if (intersection) {
        switch (render_options.mode) {
            case RenderMode::kDepth: {
                double color = intersection->first.GetDistance();
                max_color = std::max(max_color, color);
                return {color, color, color};
            }
            case RenderMode::kNormal: {
                return  .5 * intersection->first.GetNormal() + Vector{.5, .5, .5};
            }
            case RenderMode::kFull: {
                const auto color = GetIntensity(scene, intersection->first, intersection->second, ray, render_options.depth);
                max_color = std::max({max_color, color[0], color[1], color[2]});
                return color;
            }
        }
        } else {
            return render_options.mode == RenderMode::kDepth ? Vector{-1, -1, -1} : Vector{};
        }
    };
    for (size_t y_n = 0; y_n < camera_options.screen_height; ++y_n) {
        for (size_t x_n = 0; x_n < camera_options.screen_width; ++x_n) {
            const Ray ray{
              {0, 0, 0},
              {-width / 2 + pixel_size * (static_cast<double>(x_n) + .5), -height / 2 + pixel_size * (static_cast<double>(y_n) + .5), -1}};
            const Ray translated_ray = TranslateRay(basis, camera_options.look_from, ray);
            pixel_colors[camera_options.screen_height - 1 - y_n][x_n] = get_color(FindNearestIntersection(scene, translated_ray), translated_ray);
        }
    }
    if (render_options.mode == RenderMode::kDepth) {
        for (int y_n = 0; y_n < camera_options.screen_height; ++y_n) {
            for (int x_n = 0; x_n < camera_options.screen_width; ++x_n) {
                if (std::abs(pixel_colors[y_n][x_n][0] + 1) < kEpsilon) {
                    pixel_colors[y_n][x_n] *= -1;
                } else {
                    pixel_colors[y_n][x_n] *= (1 / max_color);
                }
            }
        }
    }
    Image image(camera_options.screen_width, camera_options.screen_height);
    auto process_color = [max_color, &render_options](double in) {
        if (render_options.mode == RenderMode::kFull) {
            return static_cast<uint8_t>(std::pow(in * (1 + in / std::pow(max_color, 2)) / (1 + in), 1 / 2.2) * 255);
        }
        return static_cast<uint8_t>(in * 255);
    };
    for (int y_n = 0; y_n < camera_options.screen_height; ++y_n) {
        for (int x_n = 0; x_n < camera_options.screen_width; ++x_n) {
            const auto in = pixel_colors[y_n][x_n];
            image.SetPixel({
                process_color(in[0]),
                process_color(in[1]),
                process_color(in[2]),
            }, y_n, x_n);              
        }
    }
    return image;
}
