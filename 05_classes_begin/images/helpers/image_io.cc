#include "image_io.h"

#include "05_classes_begin/images/image.h"
#include "05_classes_begin/images/matrix.h"
#include "tools/util/image.h"
#include "tools/util/rgb.h"

#include <cassert>
#include <string>

namespace {

Image ToCImg(const MatrixImage& image) {
    const auto height = image.Rows();
    const auto width = image.Columns();
    const auto& matrix = image.Data();
    Image ans_image{static_cast<int>(width), static_cast<int>(height)};
    for (int x = 0; x < static_cast<int>(width); ++x) {
        for (int y = 0; y < static_cast<int>(height); ++y) {
            ans_image.SetPixel(matrix[y][x], y, x);
        }
    }
    return ans_image;
}

Image ToCImg(const GrayscaleImage& image) {
    const auto height = image.Rows();
    const auto width = image.Columns();
    const auto& matrix = image.Data();
    Image ans_image{static_cast<int>(width), static_cast<int>(height)};
    for (int x = 0; x < static_cast<int>(width); ++x) {
        for (int y = 0; y < static_cast<int>(height); ++y) {
            ans_image.SetPixel(RGB{matrix[y][x], matrix[y][x], matrix[y][x]}, y, x);
        }
    }
    return ans_image;
}

}  // anonymous namespace

MatrixImage ReadImageFromFile(const std::string& filename) {
    return MatrixImage(Image{std::filesystem::path{filename}}.GetMatrixImage());
}

template <class Color>
void SaveImageToFile(const Matrix<Color>& image, const std::string& filename) {
    const auto img = ToCImg(image);
    img.Write(std::filesystem::path{filename});
}

template <class Color>
void DrawImage(const Matrix<Color>& image) {
    const auto img = ToCImg(image);
    // temporary don't do anything
    // img.display();
}

template void SaveImageToFile(const MatrixImage&, const std::string&);
template void SaveImageToFile(const GrayscaleImage&, const std::string&);
template void DrawImage(const MatrixImage&);
template void DrawImage(const GrayscaleImage&);
