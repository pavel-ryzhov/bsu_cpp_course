#pragma once

#include "98_raytracer/raytracer/options/camera_options.h"
#include "98_raytracer/raytracer/options/render_options.h"
#include "98_raytracer/raytracer/raytracer.h"
#include "tools/util/image.h"
#include "tools/util/rgb.h"

#include <catch2/catch_test_macros.hpp>
#include <cmath>
#include <filesystem>
#include <optional>
#include <ranges>
#include <string_view>

inline void Compare(const Image& actual, const Image& expected) {
    constexpr auto kEps = 2.;
    auto matches = 0;

    REQUIRE(actual.Width() == expected.Width());
    REQUIRE(actual.Height() == expected.Height());
    for (auto y : std::views::iota(0, actual.Height())) {
        for (auto x : std::views::iota(0, actual.Width())) {
            auto actual_data = actual.GetPixel(y, x);
            auto expected_data = expected.GetPixel(y, x);
            auto diff = PixelDistance(actual_data, expected_data);
            matches += static_cast<int>(diff < kEps);
        }
    }

    auto similarity = static_cast<double>(matches) / (actual.Width() * actual.Height());
    CHECK(similarity >= .99);
}

inline void CheckImage(
    const std::filesystem::path& tests_dir, std::string_view obj_filename,
    std::string_view result_filename, const CameraOptions& camera_options,
    const RenderOptions& render_options,
    const std::optional<std::filesystem::path>& output_path = std::nullopt) {
    auto image = Render(tests_dir / obj_filename, camera_options, render_options);
    if (output_path) {
        image.Write(*output_path);
        std::cout << "=======\n";
        std::cout << *output_path << std::endl;
        std::cout << "=======\n";
    }
    Compare(image, Image{tests_dir / result_filename});
}
