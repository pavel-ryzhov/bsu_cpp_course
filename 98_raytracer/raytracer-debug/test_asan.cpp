#include "98_raytracer/raytracer/options/camera_options.h"
#include "98_raytracer/raytracer/options/render_options.h"
#include "98_raytracer/raytracer/tests/commons.h"
#include "tools/util/util.h"

#include <catch2/catch_test_macros.hpp>
#include <cmath>
#include <numbers>
#include <string_view>

// NOLINTNEXTLINE(fuchsia-statically-constructed-objects,cert-err58-cpp)
static const auto kTestsDir = GetFileDir(__FILE__, true) / "tests";

TEST_CASE("Shading parts") {
    const CameraOptions camera_opts{640, 480};
    RenderOptions render_opts{1, RenderMode::kDepth};
    const auto test_dir = kTestsDir / "shading_parts";

    CheckImage(test_dir, "scene.obj", "depth.png", camera_opts, render_opts);
    render_opts.mode = RenderMode::kNormal;
    CheckImage(test_dir, "scene.obj", "normal.png", camera_opts, render_opts);
}

TEST_CASE("Triangle") {
    const CameraOptions camera_opts{
      .screen_width = 640,
      .screen_height = 480,
      .look_from = {0., 2., 0.},
      .look_to = {0., 0., 0.}};
    RenderOptions render_opts{1, RenderMode::kDepth};
    const auto test_dir = kTestsDir / "triangle";

    CheckImage(test_dir, "scene.obj", "depth.png", camera_opts, render_opts);
    render_opts.mode = RenderMode::kNormal;
    CheckImage(test_dir, "scene.obj", "normal.png", camera_opts, render_opts);
}

TEST_CASE("Triangle2") {
    const CameraOptions camera_opts{
      .screen_width = 640,
      .screen_height = 480,
      .look_from = {0., -2., 0.},
      .look_to = {0., 0., 0.}};
    RenderOptions render_opts{1, RenderMode::kDepth};
    const auto test_dir = kTestsDir / "triangle";

    CheckImage(test_dir, "scene.obj", "depth2.png", camera_opts, render_opts);
    render_opts.mode = RenderMode::kNormal;
    CheckImage(test_dir, "scene.obj", "normal2.png", camera_opts, render_opts);
}

TEST_CASE("Box with spheres") {
    const CameraOptions camera_opts{
      .screen_width = 640,
      .screen_height = 480,
      .fov = std::numbers::pi / 3,
      .look_from = {0., .7, 1.75},
      .look_to = {0., .7, 0.}};
    RenderOptions render_opts{4, RenderMode::kDepth};
    const auto test_dir = kTestsDir / "box";

    CheckImage(test_dir, "cube.obj", "depth.png", camera_opts, render_opts);
    render_opts.mode = RenderMode::kNormal;
    CheckImage(test_dir, "cube.obj", "normal.png", camera_opts, render_opts);
}
