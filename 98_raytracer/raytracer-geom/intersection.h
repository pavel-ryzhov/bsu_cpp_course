#pragma once

#include "98_raytracer/raytracer-geom/vector.h"

class Intersection {
   public:
    Intersection(const Vector& position, const Vector& normal, double distance);

    [[nodiscard]] const Vector& GetPosition() const;

    [[nodiscard]] const Vector& GetNormal() const;

    [[nodiscard]] double GetDistance() const;

   private:
   // data
};
