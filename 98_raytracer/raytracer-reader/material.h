#pragma once

#include "98_raytracer/raytracer-geom/vector.h"

#include <string>

struct Material {
    std::string name;
    Vector ambient_color{0., 0., 0.};   // Ka  I_ambient
    Vector diffuse_color{0., 0., 0.};   // Kd  I_diffuse
    Vector specular_color{0., 0., 0.};  // Ks  I_specular
    Vector intensity{0., 0., 0.};       // Ke  I_ambient
    double specular_exponent{1.};       // Ns  I_specular
    double refraction_index{1.};        // Ni  I_refract
    Vector albedo{1., 0., 0.};          // al
};
