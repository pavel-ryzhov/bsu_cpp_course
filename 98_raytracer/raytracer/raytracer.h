#pragma once

#include "98_raytracer/raytracer-geom/geometry.h"
#include "98_raytracer/raytracer-geom/ray.h"
#include "98_raytracer/raytracer-reader/scene.h"
#include "98_raytracer/raytracer/options/camera_options.h"
#include "98_raytracer/raytracer/options/render_options.h"
#include "tools/util/image.h"

#include <filesystem>
#include <optional>

inline Image Render(
    const std::filesystem::path& /*path*/, const CameraOptions& /*camera_options*/,
    const RenderOptions& /*render_options*/) {
    throw std::runtime_error{"Not implemented"};
}
