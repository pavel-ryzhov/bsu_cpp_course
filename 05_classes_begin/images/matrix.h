#pragma once

#include <stdexcept>
#include <vector>

template <class T>
class Matrix {
   public:
    [[nodiscard]] size_t Rows() const;

    [[nodiscard]] size_t Columns() const;

    const std::vector<std::vector<T>>& Data() const;
};

template <class T>
inline Matrix<T> Transpose(const Matrix<T>& /*unused*/) {
    throw std::runtime_error{"Not implemented"};
}
