#pragma once

#include <vector>

template <class T>
class Matrix {
   public:
    [[nodiscard]] size_t Rows() const;

    [[nodiscard]] size_t Columns() const;

    const std::vector<std::vector<T>>& Data() const;
};
