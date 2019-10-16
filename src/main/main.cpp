#include "geometry/vec3d.h"
#include "graphic/color.h"
#include "graphic/hittable_list.h"
#include "graphic/ray.h"
#include "graphic/sphere.h"

#include <cmath>
#include <fstream>
#include <iostream>
#include <memory>
#include <unistd.h>

namespace graphic {
std::ostream& operator<<(std::ostream& out, const color& cr) noexcept {
    out << cr.r << " " << cr.g << " " << cr.b;
    return out;
}
}

namespace {
graphic::color to_color(const graphic::ray& ray, const graphic::hittable_list& world) noexcept {
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
        const float ratio = 0.5f * (ray.direction().y + 1.0f);

        return (1.0f - ratio) * color{ 255, 255, 255 } + ratio * color{ 127, 178, 255 };
    }
}

bool is_grid(const geometry::vec3d& u, const geometry::vec3d& v) {
    const float roundx = std::round(u.x * 2);
    const float roundy = std::round(v.y * 2);
    return std::fabs(roundx - u.x * 2) < 0.001 || std::fabs(roundy - v.y * 2) < 0.001;
}
}

int main() {
    constexpr int nx = 2000;
    constexpr int ny = 1000;
    constexpr float window_distance = -20.0f;

    constexpr geometry::vec3d lower_left_corner = { -2.0f, -1.0f, window_distance };
    constexpr geometry::vec3d horizontal = { 4.0f, 0.0f, 0.0f };
    constexpr geometry::vec3d vertical = { 0.0f, 2.0f, 0.0f };
    constexpr geometry::vec3d origin = { 0.0f, 0.0f, 0.0f };
    for (int p = -3; p <= 3; ++p) {
        std::cerr << p << "\n";
        std::ofstream out("/home/marcelo/tmp/img-" + std::to_string(p + 3) + ".ppm");
        out << "P3\n"
                  << nx << " " << ny << "\n255\n";
        const float x = float(p) - 1.0f;
        std::vector<std::unique_ptr<graphic::hittable>> hittables;
        hittables.push_back(std::make_unique<graphic::sphere>(geometry::vec3d{ x + 0, 0.5, window_distance }, 0.3));
        hittables.push_back(std::make_unique<graphic::sphere>(geometry::vec3d{ x + 1, 0, window_distance - 4 }, 0.5));
        hittables.push_back(std::make_unique<graphic::sphere>(geometry::vec3d{ x + 2, -0.2, window_distance - 10 }, 1));

        graphic::hittable_list world(std::move(hittables));

        for (int j = 0; j < ny; ++j) {
            const float v = float(j) / float(ny);
            const auto dv = v * vertical;

            for (int i = 0; i < nx; ++i) {
                const float u = float(i) / float(nx);
                const auto dh = u * horizontal;


                if (is_grid(dh, dv)) {
                    out << "0 0 0\n";
                } else {
                    const graphic::ray r{ origin, lower_left_corner + dh + dv };
                    const graphic::color col = to_color(r, world);
                    out << col << "\n";
                }
            }
        }
        out.close();
    }
}
