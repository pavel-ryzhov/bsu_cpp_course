#pragma once

#include <cstddef>
#include <stdexcept>
#include <vector>

template <class T>
class Matrix {
   public:
    static Matrix Identity(size_t n) {
        Matrix matrix(n, n, static_cast<T>(0));
        for (size_t i = 0; i < n; i++) {
            matrix(i, i) = static_cast<T>(1);
        }
        return matrix;
    }

    Matrix(size_t n, size_t m, const T& value = T()) : rows_(n), columns_(m) {
        data_.resize(n, std::move(std::vector<T>(m, value)));
    }

    explicit Matrix(size_t n) : Matrix(n, n, T()) {
    }

    explicit Matrix(std::vector<std::vector<T> > matrix) {
        if (matrix.empty() || matrix.front().empty()) {
            throw std::invalid_argument("Empty matrix!");
        }
        const size_t columns = matrix.front().size();
        for (size_t i = 1; i < matrix.size(); i++) {
            if (matrix[i].size() != columns) {
                throw std::invalid_argument("Not a matrix!");
            }
        }
        columns_ = columns;
        rows_ = matrix.size();
        data_ = std::move(matrix);
    }

    Matrix(const Matrix& matrix) = default;

    Matrix(Matrix&& matrix) noexcept = default;

    Matrix& operator=(const Matrix& matrix) = default;

    Matrix& operator=(Matrix&& matrix) noexcept = default;

    ~Matrix() = default;

    const T& operator()(size_t i, size_t j) const {
        CheckCoords(i, j);
        return data_[i][j];
    }

    T& operator()(size_t i, size_t j) {
        CheckCoords(i, j);
        return data_[i][j];
    }

    Matrix& operator+=(const Matrix& matrix) {
        ForEach([&](size_t i, size_t j) { (*this)(i, j) += matrix(i, j); });
        return *this;
    }

    Matrix& operator-=(const Matrix& matrix) {
        ForEach([&](size_t i, size_t j) { (*this)(i, j) -= matrix(i, j); });
        return *this;
    }

    Matrix operator+(const Matrix& matrix) const {
        Matrix m = *this;
        m += matrix;
        return m;
    }

    Matrix operator-(const Matrix& matrix) const {
        Matrix m = *this;
        m -= matrix;
        return m;
    }

    Matrix& operator*=(const Matrix& matrix) {
        *this = *this * matrix;
        return *this;
    }

    Matrix operator*(const Matrix& matrix) const {
        const size_t l = this->rows_;
        const size_t m = matrix.rows_;
        const size_t n = matrix.columns_;
        Matrix result(l, n);
        for (size_t i = 0; i < l; i++) {
            for (size_t j = 0; j < n; j++) {
                T a = 0;
                for (size_t r = 0; r < m; r++) {
                    a += (*this)(i, r) * matrix(r, j);
                }
                result(i, j) = a;
            }
        }
        return result;
    }

    bool operator==(const Matrix& matrix) const {
        if (this->rows_ != matrix.rows_ || this->columns_ != matrix.columns_) {
            return false;
        }
        for (size_t i = 0; i < this->rows_; i++) {
            for (size_t j = 0; j < this->columns_; j++) {
                if ((*this)(i, j) != matrix(i, j)) {
                    return false;
                }
            }
        }
        return true;
    }

    bool operator!=(const Matrix& matrix) const {
        return !(*this == matrix);
    }

    [[nodiscard]] Matrix Transpose() const {
        Matrix transposed(columns_, rows_);
        ForEach([&](size_t i, size_t j) { transposed(j, i) = (*this)(i, j); });
        return transposed;
    }

    [[nodiscard]] size_t Rows() const {
        return rows_;
    }

    [[nodiscard]] size_t Columns() const {
        return columns_;
    }

    [[nodiscard]] const std::vector<std::vector<T> >& Data() const {
        return data_;
    }

   private:
    std::vector<std::vector<T> > data_;
    size_t rows_;
    size_t columns_;

    void CheckCoords(size_t i, size_t j) const {
        if (i >= rows_ || j >= columns_) {
            throw std::invalid_argument("Coordinates out of range!");
        }
    }

    template <typename Function>
    void ForEach(Function function) const {
        for (size_t i = 0; i < rows_; i++) {
            for (size_t j = 0; j < columns_; j++) {
                function(i, j);
            }
        }
    }
};

template <class T>
Matrix<T> Transpose(const Matrix<T>& matrix) {
    return matrix.Transpose();
}