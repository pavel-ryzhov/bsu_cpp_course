#pragma once

#include "98_raytracer/raytracer-geom/vector.h"
#include "98_raytracer/raytracer-reader/light.h"
#include "98_raytracer/raytracer-reader/material.h"
#include "98_raytracer/raytracer-reader/object.h"

#include <algorithm>
#include <cmath>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

class Scene {
   public:
    [[nodiscard]] const std::vector<TriangleObject>& GetObjects() const;

    [[nodiscard]] const std::vector<SphereObject>& GetSphereObjects() const;

    [[nodiscard]] const std::vector<Light>& GetLights() const;

    [[nodiscard]] const std::unordered_map<std::string, Material>& GetMaterials() const;
};

inline std::unordered_map<std::string, Material> ReadMaterials(const std::filesystem::path& path);

inline Scene ReadScene(const std::filesystem::path& path);
