#pragma once

#include "05_classes_begin/images/image.h"
#include "05_classes_begin/images/matrix.h"

#include <string>

MatrixImage ReadImageFromFile(const std::string& filename);

template <class Color>
void SaveImageToFile(const Matrix<Color>& image, const std::string& filename);

template <class Color>
void DrawImage(const Matrix<Color>& image);
