#include "image.h"
#include "matrix.h"
#include "tools/util/rgb.h"

#include <catch2/catch_test_macros.hpp>
#include <cstdint>
#include <vector>

using RGBVector = std::vector<std::vector<RGB>>;

TEST_CASE("FlipHorizontally") {
    const MatrixImage a({{kBlack, kWhite}, {kRed, kGreen}});
    CHECK(FlipHorizontally(a).Data() == RGBVector{{kWhite, kBlack}, {kGreen, kRed}});
}

TEST_CASE("ToGray") {
    const MatrixImage a({{{0, 255, 129}, {0, 0, 2}, {255, 255, 255}, {127, 128, 129}}});
    CHECK(ToGray(a).Data() == std::vector<std::vector<uint8_t>>{{128, 0, 255, 128}});
}

TEST_CASE("Blend") {
    const MatrixImage a({
      {kBlack, kBlack, kBlack},
      {kRed, kRed, kRed},
      {kWhite, kWhite, kWhite},
      {kGray, kGray, kGray},
    });
    const MatrixImage b({
      {kWhite, kYellow, kWhite},
      {kWhite, kYellow, kRed},
      {kWhite, kYellow, kWhite},
      {kWhite, kYellow, kBlack},
    });
    CHECK(
        Blend(a, b).Data() ==
        RGBVector{
          {kBlack, RGB{127, 127, 0}, kWhite},
          {kRed, RGB{255, 127, 0}, kRed},
          {kWhite, RGB{255, 255, 127}, kWhite},
          {kGray, RGB{191, 191, 64}, kBlack}});
}

TEST_CASE("Rotate") {
    const MatrixImage a({{kBlack, kWhite}, {kRed, kGreen}, {kBlue, kYellow}});
    CHECK(RotateClockwise(a).Data() == RGBVector{{kBlue, kRed, kBlack}, {kYellow, kGreen, kWhite}});
}

TEST_CASE("MixChannels") {
    const MatrixImage a({{kWhite, kGray, kBlack, kRed, kGreen, kBlue, kYellow}});

    const Matrix<float> to_gray(
        {{1. / 3, 1. / 3, 1. / 3}, {1. / 3, 1. / 3, 1. / 3}, {1. / 3, 1. / 3, 1. / 3}});
    CHECK(
        MixChannels(a, to_gray).Data() ==
        RGBVector{{kWhite, kGray, kBlack, kLightgray, kLightgray, kLightgray, RGB{170, 170, 170}}});

    const Matrix<float> swap_channels({{0, 1, 0}, {0, 0, 1}, {1, 0, 0}});
    CHECK(
        MixChannels(a, swap_channels).Data() ==
        RGBVector{{kWhite, kGray, kBlack, kBlue, kRed, kGreen, RGB{255, 0, 255}}});

    const Matrix<float> darken({{0.5, 0, 0}, {0, 0.5, 0}, {0, 0, 0.5}});
    CHECK(
        MixChannels(a, darken).Data() ==
        RGBVector{
          {RGB{127, 127, 127}, RGB{64, 64, 64}, kBlack, RGB{127, 0, 0}, RGB{0, 127, 0},
           RGB{0, 0, 127}, RGB{127, 127, 0}}});
}
