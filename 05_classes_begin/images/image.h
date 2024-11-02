#pragma once

#include "matrix.h"
#include "tools/util/rgb.h"

#include <algorithm>
#include <cstddef>
#include <cstdint>

using MatrixImage = Matrix<RGB>;
using RGBImage = Matrix<RGB>;
using GrayscaleImage = Matrix<uint8_t>;

template <class T>
Matrix<T> FlipHorizontally(const Matrix<T>& matrix) {
    Matrix<T> result = matrix;
    for (size_t i = 0; i < result.Rows(); i++) {
        for (size_t j = 0; j < result.Columns() / 2; j++) {
            std::swap(result(i, j), result(i, result.Columns() - j - 1));
        }
    }
    return result;
}

inline GrayscaleImage ToGray(const RGBImage& matrix) {
    GrayscaleImage result(matrix.Rows(), matrix.Columns());
    for (size_t i = 0; i < matrix.Rows(); i++) {
        for (size_t j = 0; j < matrix.Columns(); j++) {
            const auto color = matrix(i, j);
            result(i, j) = (color.r + color.g + color.b) / 3;
        }
    }
    return result;
}

inline uint8_t BlendComponent(uint8_t a, uint8_t b, float alpha) {
    return static_cast<uint8_t>(
        (static_cast<float>(b) * alpha) + (static_cast<float>(a) * (1 - alpha)));
}

inline RGB BlendSum(const RGB a, const RGB b, const float alpha) {
    const uint8_t red = BlendComponent(a.r, b.r, alpha);
    const uint8_t green = BlendComponent(a.g, b.g, alpha);
    const uint8_t blue = BlendComponent(a.b, b.b, alpha);
    return RGB(red, green, blue);
}

inline RGBImage Blend(const RGBImage& left, const RGBImage& right) {
    RGBImage result(left.Rows(), left.Columns());
    for (size_t i = 0; i < left.Columns(); i++) {
        const float alpha = static_cast<float>(i) / static_cast<float>(left.Columns() - 1);
        for (size_t j = 0; j < left.Rows(); j++) {
            result(j, i) = BlendSum(left(j, i), right(j, i), alpha);
        }
    }
    return result;
}

template <class T>
Matrix<T> RotateClockwise(const Matrix<T>& matrix) {
    return FlipHorizontally(matrix.Transpose());
}

inline uint8_t FloatColorToUInt8T(float color) {
    if (color > 255) {
        return 255;
    }
    if (color < 0) {
        return 0;
    }
    return static_cast<uint8_t>(color);
}

inline RGBImage MixChannels(
    [[maybe_unused]] const RGBImage& image, [[maybe_unused]] const Matrix<float>& filter) {
    RGBImage result(image.Rows(), image.Columns());
    for (size_t i = 0; i < result.Rows(); i++) {
        for (size_t j = 0; j < result.Columns(); j++) {
            const RGB rgb = image(i, j);
            const Matrix<float> color(
                {{static_cast<float>(rgb.r), static_cast<float>(rgb.g),
                  static_cast<float>(rgb.b)}});
            const Matrix<float> result_color = (filter * color.Transpose()).Transpose();
            auto red = FloatColorToUInt8T(result_color.Data().front()[0]);
            auto green = FloatColorToUInt8T(result_color.Data().front()[1]);
            auto blue = FloatColorToUInt8T(result_color.Data().front()[2]);
            result(i, j) = RGB(red, green, blue);
        }
    }
    return result;
}

inline RGBImage Convolve(
    [[maybe_unused]] const RGBImage& image, [[maybe_unused]] const Matrix<float>& kernel) {
    RGBImage result(image.Rows() - kernel.Rows() + 1, image.Columns() - kernel.Columns() + 1);
    const size_t kernel_half_rows = kernel.Rows() / 2;
    const size_t kernel_half_columns = kernel.Columns() / 2;
    for (size_t y = kernel_half_rows; y < image.Rows() - kernel_half_rows; y++) {
        for (size_t x = kernel_half_columns; x < image.Columns() - kernel_half_columns; x++) {
            float sum_r = 0;
            float sum_g = 0;
            float sum_b = 0;
            for (size_t i = 0; i < kernel.Rows(); i++) {
                for (size_t j = 0; j < kernel.Columns(); j++) {
                    const auto k = kernel(i, j);
                    const auto [r, g, b] =
                        image(x - kernel_half_rows + i, y - kernel_half_columns + j);
                    sum_r += k * static_cast<float>(r);
                    sum_g += k * static_cast<float>(g);
                    sum_b += k * static_cast<float>(b);
                    result(y - kernel_half_rows, x - kernel_half_columns) =
                        RGB(FloatColorToUInt8T(sum_r), FloatColorToUInt8T(sum_g),
                            FloatColorToUInt8T(sum_b));
                }
            }
        }
    }
    return result;
}
