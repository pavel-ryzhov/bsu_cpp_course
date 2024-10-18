#include "98_raytracer/raytracer/options/camera_options.h"
#include "98_raytracer/raytracer/tests/commons.h"
#include "tools/util/util.h"

#include <catch2/catch_test_macros.hpp>
#include <cmath>
#include <string_view>

// NOLINTNEXTLINE(cert-err58-cpp,fuchsia-statically-constructed-objects)
static const auto kTestsDir = GetFileDir(__FILE__, true) / "tests";

TEST_CASE("Classic box") {
    CameraOptions camera_opts{
      .screen_width = 500,
      .screen_height = 500,
      .look_from = {-.5, 1.5, .98},
      .look_to = {0., 1., 0.}};
    const auto test_dir = kTestsDir / "classic_box";

    CheckImage(test_dir, "CornellBox.obj", "first.png", camera_opts, {4});
    camera_opts.look_from = {-.9, 1.9, -1};
    camera_opts.look_to = {0., 0., 0.};
    CheckImage(test_dir, "CornellBox.obj", "second.png", camera_opts, {4});
}

TEST_CASE("Mirrors") {
    const CameraOptions camera_opts{
      .screen_width = 800,
      .screen_height = 600,
      .look_from = {2., 1.5, -.1},
      .look_to = {1., 1.2, -2.8}};
    const auto test_dir = kTestsDir / "mirrors";

    CheckImage(test_dir, "scene.obj", "result.png", camera_opts, {9});
}

TEST_CASE("Distorted box") {
    const CameraOptions camera_opts{
      .screen_width = 500,
      .screen_height = 500,
      .look_from = {-0.5, 1.5, 1.98},
      .look_to = {0., 1., 0.}};
    const auto test_dir = kTestsDir / "distorted_box";

    CheckImage(test_dir, "CornellBox.obj", "result.png", camera_opts, {4});
}

TEST_CASE("Deer") {
    const CameraOptions camera_opts{
      .screen_width = 500,
      .screen_height = 500,
      .look_from = {100., 200., 150.},
      .look_to = {0., 100., 0.}};
    const auto test_dir = kTestsDir / "deer";

    CheckImage(test_dir, "CERF_Free.obj", "result.png", camera_opts, {1});
}
