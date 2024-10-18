#pragma once

#include "vector.h"

#include <cassert>
#include <cmath>
#include <cstdint>

class Triangle {
   public:
    Triangle(const Vector& a, const Vector& b, const Vector& c);

    const Vector& operator[](size_t ind) const;

    [[nodiscard]] double Area() const;

   private:
    // data
};
