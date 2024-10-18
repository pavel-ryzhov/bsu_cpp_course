#pragma once

#include <array>
#include <cassert>
#include <cmath>
#include <cstddef>
#include <iostream>
#include <ostream>

class Vector {
   public:
    Vector() = default;

    Vector(double x, double y, double z);

    double& operator[](size_t ind);

    double operator[](size_t ind) const;

    void Normalize();

   private:
    // data
};

inline double DotProduct(const Vector& a, const Vector& b);

inline Vector CrossProduct(const Vector& a, const Vector& b);

inline double Length(const Vector& v);
