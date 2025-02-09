#pragma once

#include "98_raytracer/raytracer-geom/vector.h"

class Intersection {
   public:
    Intersection(const Vector& position, const Vector& normal, double distance, bool is_inside) : position_(position), normal_(normal), distance_(distance), is_inside_(is_inside) {
        normal_.Normalize();
    }

    Intersection(const Vector& position, const Vector& normal, double distance) : Intersection(position, normal, distance, false) {
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

    [[nodiscard]] bool IsInside() const {
        return is_inside_;
    }

   private:
    Vector position_;
    Vector normal_;
    double distance_;
    bool is_inside_;
};

inline std::ostream& operator<<(std::ostream& os, const Intersection& v) {
    return os << "Intersection{" << v.GetPosition() << ", " << v.GetNormal() << ", " << v.GetDistance() << "}";
}
