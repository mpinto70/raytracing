#include "geometry/vec3d.h"
#include "graphic/color.h"
#include "graphic/ray.h"

#include <iostream>

namespace graphic {
std::ostream& operator<<(std::ostream& out, const color& cr) {
    out << cr.r << " " << cr.g << " " << cr.b;
    return out;
}
}

namespace {
graphic::color to_color(const graphic::ray& ray) {
    const auto unit_direction = geometry::unity(ray.direction);
    const float t = 0.5f * (unit_direction.y + 1.0f);

    return (1.0f - t) * graphic::color{ 0, 255, 0 } + t * graphic::color{ 255, 0, 0 };
}
}

int main() {
    int nx = 200;
    int ny = 100;
    std::cout << "P3\n"
              << nx << " " << ny << "\n255\n";

    constexpr geometry::vec3d lower_left_corner = { -2.0f, -1.0f, -1.0f };
    constexpr geometry::vec3d horizontal = { 4.0f, 0.0f, 0.0f };
    constexpr geometry::vec3d vertical = { 0.0f, 2.0f, 0.0f };
    constexpr geometry::vec3d origin = { 0.0f, 0.0f, 0.0f };

    for (int j = ny - 1; j >= 0; j--) {
        for (int i = 0; i < nx; i++) {
            const float u = float(i) / float(nx);
            const float v = float(j) / float(ny);
            const graphic::ray r{ origin, lower_left_corner + u * horizontal + v * vertical };
            const graphic::color col = to_color(r);
            std::cout << col << "\n";
        }
    }
}
