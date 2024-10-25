#include "image.h"
#include "matrix.h"
#include "tools/util/rgb.h"

#include <catch2/catch_message.hpp>
#include <catch2/catch_test_macros.hpp>
#include <vector>

using RGBVector = std::vector<std::vector<RGB>>;
using FloatVector = std::vector<std::vector<float>>;

TEST_CASE("Convolve") {
    const MatrixImage image({
      {kRed, kGreen, kRed, kGreen},
      {kGreen, kBlue, kBlue, kGreen},
      {kBlack, kWhite, kBlack, kWhite},
      {kWhite, kRed, kRed, kWhite},
    });

    CHECK(
        Convolve(image, Matrix<float>({{0, 0}, {0, 1}})).Data() ==
        RGBVector{
          {kBlue, kBlue, kGreen},
          {kWhite, kBlack, kWhite},
          {kRed, kRed, kWhite},
        });
    CHECK(
        Convolve(image, Matrix<float>(FloatVector{{1}, {1}})).Data() ==
        RGBVector{
          {kYellow, kCyan, kPurple, kGreen},
          {kGreen, kWhite, kBlue, kWhite},
          {kWhite, kWhite, kRed, kWhite},
        });
    CHECK(
        Convolve(image, Matrix<float>(FloatVector{{1}, {-1}})).Data() ==
        RGBVector{
          {kRed, kGreen, kRed, kBlack},
          {kGreen, kBlack, kBlue, kBlack},
          {kBlack, kCyan, kBlack, kBlack},
        });
    CHECK(
        Convolve(image, Matrix<float>({{0.2, 0.4}, {0, 0.6}})).Data() ==
        RGBVector{
          {RGB{51, 102, 153}, RGB{102, 51, 153}, RGB{51, 255, 0}},
          {RGB{153, 204, 255}, RGB{0, 0, 153}, RGB{153, 255, 204}},
          {RGB{255, 102, 102}, RGB{204, 51, 51}, kWhite},
        });
    CHECK(
        Convolve(
            image, Matrix<float>({
                     {0.4, 0, -50, 0},
                     {0, 0, -1. / 255, -0.8},
                     {0, 1, -20, 0},
                     {0, 50, -0.8, 0},
                   }))
            .Data() == RGBVector{{RGB{153, 51, 254}}});
}
