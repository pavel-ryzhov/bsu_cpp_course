#pragma once
#include "matrix.h"
#include "tools/util/rgb.h"

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <stdexcept>

using MatrixImage = Matrix<RGB>;
using RGBImage = Matrix<RGB>;
using GrayscaleImage = Matrix<uint8_t>;

template <class T>
inline Matrix<T> FlipHorizontally(const Matrix<T>&) {
    throw std::runtime_error{"Not implemented"};
}

inline GrayscaleImage ToGray(const RGBImage&) {
    throw std::runtime_error{"Not implemented"};
}

inline RGBImage Blend(const RGBImage&, const RGBImage&) {
    throw std::runtime_error{"Not implemented"};
}

template <class T>
inline Matrix<T> RotateClockwise(const Matrix<T>&) {
    throw std::runtime_error{"Not implemented"};
}

inline RGBImage MixChannels(
    [[maybe_unused]] const RGBImage& image, [[maybe_unused]] const Matrix<float>& filter) {
    throw std::runtime_error{"Not implemented"};
}

inline RGBImage Convolve(
    [[maybe_unused]] const RGBImage& image, [[maybe_unused]] const Matrix<float>& kernel) {
    throw std::runtime_error{"Not implemented"};
}
