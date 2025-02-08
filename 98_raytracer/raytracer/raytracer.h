#pragma once

#include "98_raytracer/raytracer-geom/geometry.h"
#include "98_raytracer/raytracer-geom/intersection.h"
#include "98_raytracer/raytracer-geom/ray.h"
#include "98_raytracer/raytracer-geom/vector.h"
#include "98_raytracer/raytracer-reader/object.h"
#include "98_raytracer/raytracer-reader/scene.h"
#include "98_raytracer/raytracer/options/camera_options.h"
#include "98_raytracer/raytracer/options/render_options.h"
#include "tools/util/image.h"

#include <algorithm>
#include <array>
#include <catch2/catch_test_macros.hpp>
#include <cmath>
#include <concepts>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <filesystem>
#include <optional>
#include <vector>

static std::array<Vector, 3> CalculateBasis(Vector new_k) {
    new_k.Normalize();
    auto new_i = CrossProduct({0, 1, 0}, new_k);
    auto new_j = CrossProduct(new_k, new_i);
    if (new_i.Length() < kEpsilon) [[unlikely]] {
        new_j = CrossProduct(new_k, {1, 0, 0});
        new_i = CrossProduct(new_j, new_k);
    }
    new_i.Normalize();
    new_j.Normalize();
    std::cout << new_i << std::endl;
    std::cout << new_j << std::endl;
    std::cout << new_k << std::endl;
    return {new_i, new_j, new_k};
}

static Vector TranslateVector(
    const std::array<Vector, 3>& basis, const Vector& coords) {
    const auto x = DotProduct(coords, {basis[0][0], basis[1][0], basis[2][0]});
    const auto y = DotProduct(coords, {basis[0][1], basis[1][1], basis[2][1]});
    const auto z = DotProduct(coords, {basis[0][2], basis[1][2], basis[2][2]});
    return {x, y, z};
}

static Vector TranslatePoint(
    const std::array<Vector, 3>& basis, const Vector& r0, const Vector& coords) {
    return TranslateVector(basis, coords) + r0;
}

static Ray TranslateRay(const std::array<Vector, 3>& basis, const Vector& r0, const Ray& ray) {
    return {
      TranslatePoint(basis, r0, ray.GetOrigin()), TranslateVector(basis, ray.GetDirection())};
}

template <class T>
requires std::same_as<T, TriangleObject> || std::same_as<T, SphereObject>
void FindNearestIntersection(
    std::optional<Intersection>& nearest_intersection, const std::vector<T> objects, const Ray& ray) {
    for (const auto& object : objects) {      
        if (const auto intersection = GetIntersection(ray, object); intersection && (!nearest_intersection || intersection->GetDistance() < nearest_intersection->GetDistance())) {
            nearest_intersection = intersection;
        }
    }
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
    double max_distance = 0;
    double max_color = 0;
    auto get_color = [&max_distance, &max_color, &render_options](const std::optional<Intersection>& intersection) -> Vector {
        switch (render_options.mode) {
            case RenderMode::kDepth: {
                if (intersection) {
                    double color = intersection->GetDistance();
                    max_distance = std::max(max_distance, color);
                    return {color, color, color};
                }
                max_color = 1;
                return {-1, -1, -1};
            }
            case RenderMode::kNormal: {
                if (intersection) {
                    const auto result = .5 * intersection->GetNormal() + Vector{.5, .5, .5};
                    max_color = std::max({max_color, result[0], result[1], result[2]});
                    return result;
                }
                return {0, 0, 0};
            }
            case RenderMode::kFull: {
                return {};
            }
        }
    };
    for (size_t y_n = 0; y_n < camera_options.screen_height; ++y_n) {
        for (size_t x_n = 0; x_n < camera_options.screen_width; ++x_n) {
            const Ray ray{
              {0, 0, 0},
              {-width / 2 + pixel_size * (static_cast<double>(x_n) + .5), -height / 2 + pixel_size * (static_cast<double>(y_n) + .5), -1}};
            const Ray translated_ray = TranslateRay(basis, camera_options.look_from, ray);
            std::optional<Intersection> nearest_intersection;
            FindNearestIntersection(nearest_intersection, scene.GetSphereObjects(), translated_ray);
            FindNearestIntersection(nearest_intersection, scene.GetObjects(), translated_ray);
            // if (nearest_intersection) {
            //     pixel_colors[y_n][x_n] = get_color(*nearest_intersection);
            // } else {
            //     pixel_colors[y_n][x_n] = {-1, -1, -1};
            // }
            pixel_colors[camera_options.screen_height - 1 - y_n][x_n] = get_color(nearest_intersection);
            // if (x_n == 319 && y_n == 290) {
            if (x_n == 249 && y_n == 249) {
                // const Vector v1{-width / 2 + pixel_size * (static_cast<double>(0) + .5), -height / 2 + pixel_size * (static_cast<double>(y_n) + .5), -1};
                // const Vector v2{-width / 2 + pixel_size * (static_cast<double>(499) + .5), -height / 2 + pixel_size * (static_cast<double>(y_n) + .5), -1};
                // std::cout << "===?===\n" << TranslateCoords(basis, camera_options.look_from, v1) << std::endl;
                // std::cout << TranslateCoords(basis, camera_options.look_from, v2) << std::endl;
                // std::cout << GetIntersection(translated_ray, scene.GetObjects()[0].GetInner()).has_value();
                // std::cout << scene.GetObjects()[0].GetInner() << std::endl;
                // std::cout << basis[0] << " " << basis[1] << " " << basis[2] << std::endl;
                // std::cout << "ffff" << translated_ray << std::endl;
                // std::cout << CrossProduct(translated_ray.GetDirection(), basis[0]) << std::endl;
                // std::cout << translated_ray << std::endl;
                // FAIL("YYYYY");
            }
        }
    }
    if (render_options.mode == RenderMode::kDepth) {
        for (int y_n = 0; y_n < camera_options.screen_height; ++y_n) {
            for (int x_n = 0; x_n < camera_options.screen_width; ++x_n) {
                if (std::abs(pixel_colors[y_n][x_n][0] + 1) < kEpsilon) {
                    pixel_colors[y_n][x_n] *= -1;
                } else {
                    pixel_colors[y_n][x_n] *= (1 / max_distance);
                    max_color = std::max(max_color, pixel_colors[y_n][x_n][0]);
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
            const auto in = pixel_colors[y_n][x_n]; //TODO()
            // const auto in = pixel_colors[y_n][x_n] * (1 / max_distance); //TODO()
            if (in[0] > 1) {
                FAIL("FAIL");
            }
            image.SetPixel({
                process_color(in[0]),
                process_color(in[1]),
                process_color(in[2]),
            }, y_n, x_n);              
        }
    }
    return image;
}
