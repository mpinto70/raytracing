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
bool hit_sphere(const geometry::vec3d& center, float radius, const graphic::ray& r) {
    using geometry::vec3d;

    const vec3d oc = r.origin - center;

    const float a = dot(r.direction, r.direction);
    const float b = 2.0f * dot(oc, r.direction);
    const float c = dot(oc, oc) - radius * radius;

    float discriminant = b * b - 4 * a * c;

    return discriminant >= 0.0f;
}

graphic::color to_color(const graphic::ray& ray) {
    using geometry::vec3d;

    if (hit_sphere({ 0, 0, -1 }, 0.5f, ray)) {
        return { 127, 0, 0 };
    }
    const auto unit_direction = unity(ray.direction);
    const float t = 0.5f * (unit_direction.y + 1.0f);

    return (1.0f - t) * graphic::color{ 255, 255, 255 } + t * graphic::color{ 127, 178, 255 };
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
