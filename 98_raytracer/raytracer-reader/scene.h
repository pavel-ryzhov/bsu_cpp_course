#pragma once

#include "98_raytracer/raytracer-geom/triangle.h"
#include "98_raytracer/raytracer-geom/vector.h"
#include "98_raytracer/raytracer-reader/light.h"
#include "98_raytracer/raytracer-reader/material.h"
#include "98_raytracer/raytracer-reader/object.h"

#include <array>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <functional>
#include <optional>
#include <sstream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

class Scene {
   public:
    [[nodiscard]] const std::vector<TriangleObject>& GetObjects() const {
        return objects_;
    }

    [[nodiscard]] const std::vector<SphereObject>& GetSphereObjects() const {
        return sphere_objects_;
    }

    [[nodiscard]] const std::vector<Light>& GetLights() const {
        return lights_;
    }

    [[nodiscard]] const std::unordered_map<std::string, Material>& GetMaterials() const {
        return materials_;
    }

   private:
    std::vector<TriangleObject> objects_;
    std::vector<SphereObject> sphere_objects_;
    std::vector<Light> lights_;
    std::unordered_map<std::string, Material> materials_;
    std::vector<Vector> vertexes_;
    std::vector<Vector> normals_;

    template <class T>
    size_t FormatIndex(int64_t index, const std::vector<T>& container) const {
        return index + (index > 0 ? -1 : container.size());
    }

    const Vector& GetVertex(int64_t index) const {
        return vertexes_[FormatIndex(index, vertexes_)];
    }

    const Vector& GetNormal(int64_t index) const {
        return normals_[FormatIndex(index, normals_)];
    }

    friend Scene ReadScene(const std::filesystem::path& path);
};

static Vector ReadVector(std::istream& is) {
    double x = 0;
    double y = 0;
    double z = 0;
    is >> x >> y >> z;
    return Vector{x, y, z};
}

inline std::unordered_map<std::string, Material> ReadMaterials(const std::filesystem::path& path) {
    std::ifstream ifs(path);
    std::unordered_map<std::string, Material> materials;
    Material current_material;
    const std::unordered_map<std::string, std::function<void()>> commands{
      {"newmtl",
       [&ifs, &current_material, &materials] {
           if (!current_material.name.empty()) [[likely]] {
               materials.emplace(current_material.name, current_material);
               current_material = Material();
           }
           std::string name;
           ifs >> name;
           current_material.name = name;
       }},
      {"Ka", [&ifs, &current_material] { current_material.ambient_color = ReadVector(ifs); }},
      {"Kd", [&ifs, &current_material] { current_material.diffuse_color = ReadVector(ifs); }},
      {"Ks", [&ifs, &current_material] { current_material.specular_color = ReadVector(ifs); }},
      {"Ke", [&ifs, &current_material] { current_material.intensity = ReadVector(ifs); }},
      {"Ns",
       [&ifs, &current_material] {
           double d = 0;
           ifs >> d;
           current_material.specular_exponent = d;
       }},
      {"Ni",
       [&ifs, &current_material] {
           double d = 0;
           ifs >> d;
           current_material.refraction_index = d;
       }},
      {"al", [&ifs, &current_material] { current_material.albedo = ReadVector(ifs); }},
    };

    std::string command;
    while (ifs.good()) {
        ifs >> command;
        if (commands.contains(command)) {
            commands.at(command)();
        }
    }
    materials.emplace(current_material.name, current_material);
    return materials;
}

static std::pair<int64_t, std::optional<int64_t>> ReadVertex(std::istream& is) {
    std::string data;
    is >> data;
    std::istringstream iss(data);
    std::getline(iss, data, '/');
    int64_t v = std::stoll(data);
    std::optional<int64_t> vn;
    if (iss.good()) {
        std::getline(iss, data, '/');
        if (iss.good()) {
            vn = 0;
            iss >> *vn;
        }
    }
    return std::pair{v, vn};
}

inline Scene ReadScene(const std::filesystem::path& path) {
    Scene scene;
    std::ifstream ifs(path);
    Material* current_material = nullptr;
    const std::unordered_map<std::string, std::function<void()>> commands{
      {"v", [&ifs, &scene] { scene.vertexes_.emplace_back(ReadVector(ifs)); }},
      {"vn", [&ifs, &scene] { scene.normals_.emplace_back(ReadVector(ifs)); }},
      {"f",
       [&ifs, &scene, &current_material] {
           std::string line;
           std::getline(ifs, line);
           std::istringstream iss(line);
           std::vector<std::pair<int64_t, std::optional<int64_t>>> vertexes;
           while (iss.good() && !iss.str().substr(static_cast<size_t>(iss.tellg()) + 1).empty()) {
               vertexes.push_back(ReadVertex(iss));
           }
           for (size_t i = 1; i < vertexes.size() - 1; ++i) {
               const Triangle triangle{
                 scene.GetVertex(vertexes[0].first),
                 scene.GetVertex(vertexes[i].first),
                 scene.GetVertex(vertexes[i + 1].first),
               };
               std::optional<const std::array<Vector, 3>> normals;
               if (vertexes[0].second) {
                   normals.emplace(std::array<Vector, 3>{
                     scene.GetNormal(*vertexes[0].second),
                     scene.GetNormal(*vertexes[i].second),
                     scene.GetNormal(*vertexes[i + 1].second),
                   });
               }
               scene.objects_.emplace_back(current_material, triangle, normals);
           }
       }},
      {"S",
       [&ifs, &current_material, &scene] {
           const auto center = ReadVector(ifs);
           double radius = 0;
           ifs >> radius;
           scene.sphere_objects_.emplace_back(current_material, center, radius);
       }},
      {"P",
       [&ifs, &scene] {
           const auto position = ReadVector(ifs);
           const auto intensity = ReadVector(ifs);
           scene.lights_.emplace_back(position, intensity);
       }},
      {"usemtl",
       [&current_material, &ifs, &scene] {
           std::string material;
           ifs >> material;
           current_material = &scene.materials_[material];
       }},
      {"mtllib",
       [&ifs, &path, &scene] {
           std::string mtl_path;
           ifs >> mtl_path;
           const auto materials = ReadMaterials(path.parent_path() / mtl_path);
           scene.materials_.insert(materials.begin(), materials.end());
       }},
    };
    std::string command;
    while (ifs.good()) {
        ifs >> command;
        if (commands.contains(command)) {
            commands.at(command)();
        }
    }
    return scene;
}
