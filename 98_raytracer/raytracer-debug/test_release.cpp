#include "98_raytracer/raytracer/options/camera_options.h"
#include "98_raytracer/raytracer/options/render_options.h"
#include "98_raytracer/raytracer/tests/commons.h"
#include "tools/util/util.h"

#include <catch2/catch_test_macros.hpp>
#include <cmath>
#include <string_view>

// NOLINTNEXTLINE(cert-err58-cpp,fuchsia-statically-constructed-objects)
static const auto kTestsDir = GetFileDir(__FILE__, true) / "tests";

constexpr auto kOutputPath = "/home/amigo/programming/projects/studing/pavelryzhov0639289/98_raytracer/raytracer-debug/out.png";

TEST_CASE("Classic box") {
    RenderOptions render_opts{4, RenderMode::kDepth};
    const auto test_dir = kTestsDir / "classic_box";
    const auto* obj_filename = "CornellBox.obj";

    {
        const CameraOptions camera_opts{
          .screen_width = 500,
          .screen_height = 500,
          .look_from = {-.5, 1.5, .98},
          .look_to = {0., 1., 0.}};

        CheckImage(test_dir, obj_filename, "depth1.png", camera_opts, render_opts);
        render_opts.mode = RenderMode::kNormal;
        CheckImage(test_dir, obj_filename, "normal1.png", camera_opts, render_opts);
    }

    {
        const CameraOptions camera_opts{
          .screen_width = 500,
          .screen_height = 500,
          .look_from = {-.9, 1.9, -1},
          .look_to = {0., 0., 0.}};
        render_opts.mode = RenderMode::kDepth;
        CheckImage(test_dir, obj_filename, "depth2.png", camera_opts, render_opts);
        render_opts.mode = RenderMode::kNormal;
        CheckImage(test_dir, obj_filename, "normal2.png", camera_opts, render_opts);
    }
}

TEST_CASE("Deer") {
    const CameraOptions camera_opts{
      .screen_width = 500,
      .screen_height = 500,
      .look_from = {100., 200., 150.},
      .look_to = {0., 100., 0.}};
    RenderOptions render_opts{1, RenderMode::kDepth};
    const auto test_dir = kTestsDir / "deer";

    CheckImage(test_dir, "CERF_Free.obj", "depth.png", camera_opts, render_opts);
    render_opts.mode = RenderMode::kNormal;
    CheckImage(test_dir, "CERF_Free.obj", "normal.png", camera_opts, render_opts);
}
