#include "98_raytracer/raytracer/options/camera_options.h"
#include "98_raytracer/raytracer/tests/commons.h"
#include "tools/util/util.h"

#include <catch2/catch_test_macros.hpp>
#include <cmath>
#include <numbers>
#include <string_view>

// NOLINTNEXTLINE(cert-err58-cpp,fuchsia-statically-constructed-objects)
static const auto kTestsDir = GetFileDir(__FILE__, true) / "tests";

constexpr auto kOutputPath = "/home/amigo/programming/projects/studing/pavelryzhov0639289/98_raytracer/raytracer/out.png";

TEST_CASE("Shading parts") {
    const CameraOptions camera_opts{640, 480};
    const auto test_dir = kTestsDir / "shading_parts";
    CheckImage(test_dir, "scene.obj", "scene.png", camera_opts, {1});
}

TEST_CASE("Triangle") {
    const CameraOptions camera_opts{
      .screen_width = 640,
      .screen_height = 480,
      .look_from = {0., 2., 0.},
      .look_to = {0., 0., 0.}};
    const auto test_dir = kTestsDir / "triangle";
    CheckImage(test_dir, "scene.obj", "scene.png", camera_opts, {1});
}

TEST_CASE("Triangle2") {
    const CameraOptions camera_opts{
      .screen_width = 640,
      .screen_height = 480,
      .look_from = {0., -2., 0.},
      .look_to = {0., 0., 0.}};
    const auto test_dir = kTestsDir / "triangle";
    CheckImage(test_dir, "scene.obj", "black.png", camera_opts, {1});
}

TEST_CASE("Box with spheres") {
    const CameraOptions camera_opts{
      // .screen_width = 640,
      // .screen_height = 480,
      .screen_width = 2540,
      .screen_height = 1680,
      .fov = std::numbers::pi / 3,
      // .look_from = {0., .7, 1.75},
      // .look_to = {0., .7, 0.}
      // .look_from = {0., .1, 1.75},
      // .look_to = {0., .6, 0.}
      .look_from = {0.1, .7, 0.75},
      .look_to = {0., .1, -0.1}
      // .look_from = {-0.5, .7, 1.75},
      // .look_to = {0., .7, 0.}
      };
    const auto test_dir = kTestsDir / "box";
    CheckImage(test_dir, "cube.obj", "cube.png", camera_opts, {10}, kOutputPath);
}
