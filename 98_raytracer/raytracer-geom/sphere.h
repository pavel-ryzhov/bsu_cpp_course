#pragma once

#include "98_raytracer/raytracer-geom/vector.h"

class Sphere {
   public:
    Sphere(const Vector& center, double radius);

    [[nodiscard]] const Vector& GetCenter() const;

    [[nodiscard]] double GetRadius() const;

   private:
    // data
};
