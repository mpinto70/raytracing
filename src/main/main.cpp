#include "geometry/vec3d.h"
#include "graphic/color.h"
#include "graphic/hittable_list.h"
#include "graphic/ray.h"
#include "graphic/sphere.h"

#include <cmath>
#include <iostream>
#include <memory>

namespace graphic {
std::ostream& operator<<(std::ostream& out, const color& cr) {
    out << cr.r << " " << cr.g << " " << cr.b;
    return out;
}
}

namespace {
graphic::color to_color(const graphic::ray& ray, const graphic::hittable_list& world) {
    using geometry::vec3d;
    using graphic::color;
    using graphic::hit_record;
    hit_record rec{};
    if (world.hit(ray, 0.0, 15000000.0f, rec)) {
        const int r = static_cast<int>((rec.normal.x + 1.0f) * 127.5f);
        const int g = static_cast<int>((rec.normal.y + 1.0f) * 127.5f);
        const int b = static_cast<int>((rec.normal.z + 1.0f) * 127.5f);
        return color{ r, g, b };
    } else {
        const auto unit_direction = unity(ray.direction);
        const float ratio = 0.5f * (unit_direction.y + 1.0f);

        return (1.0f - ratio) * color{ 255, 255, 255 } + ratio * color{ 127, 178, 255 };
    }
}
}

int main() {
    int nx = 2000;
    int ny = 1000;
    std::cout << "P3\n"
              << nx << " " << ny << "\n255\n";

    constexpr geometry::vec3d lower_left_corner = { -2.0f, -1.0f, -1.0f };
    constexpr geometry::vec3d horizontal = { 4.0f, 0.0f, 0.0f };
    constexpr geometry::vec3d vertical = { 0.0f, 2.0f, 0.0f };
    constexpr geometry::vec3d origin = { 0.0f, 0.0f, 0.0f };
    std::vector<std::unique_ptr<graphic::hittable>> hittables;
    hittables.push_back(std::make_unique<graphic::sphere>(geometry::vec3d{ -1, 0, -1 }, 0.3));
    hittables.push_back(std::make_unique<graphic::sphere>(geometry::vec3d{ 1, -1, -4 }, 2));
    graphic::hittable_list world(std::move(hittables));

    for (int j = ny - 1; j >= 0; j--) {
        for (int i = 0; i < nx; i++) {
            const float u = float(i) / float(nx);
            const float v = float(j) / float(ny);
            const graphic::ray r{ origin, lower_left_corner + u * horizontal + v * vertical };

            const graphic::color col = to_color(r, world);
            std::cout << col << "\n";
        }
    }
}
