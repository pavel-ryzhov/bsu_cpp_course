#pragma once
#include "matrix.h"
#include "tools/util/rgb.h"

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <stdexcept>

using Image = Matrix<RGB>;
using GrayscaleImage = Matrix<uint8_t>;

template <class T>
inline Matrix<T> FlipHorizontally(const Matrix<T>&) {
    throw std::runtime_error{"Not implemented"};
}

template <class T>
inline Matrix<T> Transpose(const Matrix<T>&) {
    throw std::runtime_error{"Not implemented"};
}

inline GrayscaleImage ToGray(const Image&) {
    throw std::runtime_error{"Not implemented"};
}

inline Image Blend(const Image&, const Image&) {
    throw std::runtime_error{"Not implemented"};
}

template <class T>
inline Matrix<T> RotateClockwise(const Matrix<T>&) {
    throw std::runtime_error{"Not implemented"};
}

inline Image MixChannels(const Image& image, const Matrix<float>& filter) {
    (void)image;
    (void)filter;
    throw std::runtime_error{"Not implemented"};
}

inline Image Convolve(const Image& image, const Matrix<float>& kernel) {
    (void)image;
    (void)kernel;
    throw std::runtime_error{"Not implemented"};
}
