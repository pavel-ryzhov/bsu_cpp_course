#pragma once

#include "98_raytracer/raytracer-geom/vector.h"

class Ray {
   public:
    Ray(const Vector& origin, const Vector& direction);

    [[nodiscard]] const Vector& GetOrigin() const;

    [[nodiscard]] const Vector& GetDirection() const;

   private:
    // data
};
