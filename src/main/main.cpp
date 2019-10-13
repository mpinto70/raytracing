#include "geometry/vec3d.h"
#include "graphic/color.h"
#include "graphic/ray.h"

#include <cmath>
#include <iostream>

namespace graphic {
std::ostream& operator<<(std::ostream& out, const color& cr) {
    out << cr.r << " " << cr.g << " " << cr.b;
    return out;
}
}

namespace {
float hit_sphere(const geometry::vec3d& center, float radius, const graphic::ray& r) {
    using geometry::vec3d;

    const vec3d oc = r.origin - center;

    const float a = dot(r.direction, r.direction);
    const float b = 2.0f * dot(oc, r.direction);
    const float c = dot(oc, oc) - radius * radius;

    float discriminant = b * b - 4 * a * c;

    if (discriminant < 0) {
        return -1.0f;
    } else {
        return (-b - std::sqrt(discriminant)) / (2 * a);
    }
}

graphic::color to_color(const graphic::ray& ray) {
    using geometry::vec3d;
    using graphic::color;
    constexpr vec3d center {0, 0, -1};

    const float t = hit_sphere(center, 0.5f, ray);
    if (t > 0.0f) {
        const vec3d N = unity(ray.point_at_parameter(t) - center);
        const int r = static_cast<int>((N.x + 1.0f) * 127.5f);
        const int g = static_cast<int>((N.y + 1.0f) * 127.5f);
        const int b = static_cast<int>((N.z + 1.0f) * 127.5f);
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
