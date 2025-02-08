#pragma once

#include "98_raytracer/raytracer-geom/vector.h"

class Intersection {
   public:
    Intersection(const Vector& position, const Vector& normal, double distance) : position_(position), normal_(normal), distance_(distance) {
        normal_.Normalize();
    }

    [[nodiscard]] const Vector& GetPosition() const {
        return position_;
    }

    [[nodiscard]] const Vector& GetNormal() const {
        return normal_;
    }

    [[nodiscard]] double GetDistance() const {
        return distance_;
    }

   private:
    Vector position_;
    Vector normal_;
    double distance_;
};

inline std::ostream& operator<<(std::ostream& os, const Intersection& v) {
    return os << "Intersection{" << v.GetPosition() << ", " << v.GetNormal() << ", " << v.GetDistance() << "}";
}
