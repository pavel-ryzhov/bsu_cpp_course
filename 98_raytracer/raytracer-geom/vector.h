#pragma once

#include <array>
#include <cassert>
#include <cmath>
#include <cstddef>
#include <iostream>
#include <ostream>
#include <variant>


constexpr double kEpsilon = 1e-9;

class Vector {
   public:
    Vector() = default;

    Vector(double x, double y, double z) : data_{x, y, z} {
    }

    Vector(double x, double y, double z, std::monostate /*monostate_for_normolized*/) : Vector{x, y, z} {
        Normalize();
    }

    Vector(const Vector& other, std::monostate /*monostate_for_normolized*/) : Vector(other) {
        Normalize();
    }

    [[nodiscard]] Vector Normalized() const {
        Vector tmp = *this;
        tmp.Normalize();
        return tmp;
    }

    double& operator[](size_t ind) {
        return data_.at(ind);
    }

    double operator[](size_t ind) const {
        return data_.at(ind);
    }

    [[nodiscard]] Vector operator+(const Vector& v) const {
        return {data_[0] + v[0], data_[1] + v[1], data_[2] + v[2]};
    }

    [[nodiscard]] Vector operator*(double a) const {
        return {data_[0] * a, data_[1] * a, data_[2] * a};
    }

    Vector& operator+=(const Vector& v) {
        return *this = *this + v;
    }

    Vector& operator-=(const Vector& v) {
        return *this = *this - v;
    }

    Vector& operator*=(double a) {
        data_[0] *= a;
        data_[1] *= a;
        data_[2] *= a;
        return *this;
    }

    [[nodiscard]] Vector operator-(const Vector& v) const {
        return *this + -v;
    }

    [[nodiscard]] Vector operator-() const {
        return *this * (-1);
    }

    [[nodiscard]] bool operator==(const Vector& other) const {
        return (*this - other).Length() < kEpsilon;
    }

    [[nodiscard]] double Length() const {
        return std::sqrt(std::pow(data_[0], 2) + std::pow(data_[1], 2) + std::pow(data_[2], 2));
    }

    void Normalize() {
        const double length = Length();
        data_[0] /= length;
        data_[1] /= length;
        data_[2] /= length;
    }

   private:
    std::array<double, 3> data_;
};

inline double DotProduct(const Vector& a, const Vector& b) {
    return a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
}

inline Vector CrossProduct(const Vector& a, const Vector& b) {
    return {a[1] * b[2] - b[1] * a[2], b[0] * a[2] - a[0] * b[2], a[0] * b[1] - b[0] * a[1]};
}

inline Vector HadamardProduct(const Vector& a, const Vector& b) {
    return {a[0] * b[0], a[1] * b[1], a[2] * b[2]};
}

inline double Length(const Vector& v) {
    return v.Length();
}

inline std::ostream& operator<<(std::ostream& os, const Vector& v) {
    return os << "Vector{" << v[0] << ", " << v[1] << ", " << v[2] << "}";
}

inline Vector operator*(double a, const Vector& v) {
    return v * a;
}
