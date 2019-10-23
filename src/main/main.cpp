#include "geometry/vec3d.h"
#include "graphic/camera.h"
#include "graphic/color.h"
#include "graphic/hittable_list.h"
#include "graphic/ray.h"
#include "graphic/sphere_reflexive.h"

#include <cmath>
#include <fstream>
#include <iostream>
#include <memory>

using geometry::dim_t;
namespace graphic {
std::ostream& operator<<(std::ostream& out, const color& cr) noexcept {
    out << cr.r << " " << cr.g << " " << cr.b;
    return out;
}
}

namespace {
graphic::color to_color(const graphic::ray& ray, const graphic::hittable_list& world, int bounces = 0) noexcept {
    using geometry::vec3d;
    using graphic::color;
    using graphic::hit_record;
    constexpr color DEFAULT_COLOR{ 0xff, 0xff, 0xff };
    if (bounces == 100) {
        return DEFAULT_COLOR;
    }
    hit_record rec{};
    if (const auto hit_object = world.hit(ray, 0.01, dim_t(15000000.0), rec)) {
        const auto next_ray = hit_object->get().bounce(ray, rec);
        if (not next_ray) {
            const auto continuation_ray = graphic::ray(rec.p, ray.direction());

            return to_color(continuation_ray, world, ++bounces);
        } else {
            auto color = to_color(*next_ray, world, ++bounces);
            color = hit_object->get().dim(color);

            return color;
        }
    } else {
        return DEFAULT_COLOR;
    }
}
}

int main() {
    using geometry::vec3d;

    constexpr int nx = 2000;
    constexpr int ny = 1000;
    constexpr auto window_position = dim_t(-1.0);
    constexpr auto camera_position = dim_t(100.0);

    constexpr vec3d lower_left_corner = { dim_t(-2.0), dim_t(-1.0), window_position };
    constexpr vec3d origin = { dim_t(0.0), dim_t(0.0), camera_position };
    graphic::camera cam(origin, lower_left_corner, 4, 2);
    for (int p = 0; p <= 0; ++p) {
        std::cerr << p << "\n";
        std::ofstream out("/home/marcelo/tmp/img-" + std::to_string(p + 3) + ".ppm");
        out << "P3\n"
            << nx << " " << ny << "\n255\n";
        std::vector<std::unique_ptr<graphic::hittable>> hittables;
        hittables.push_back(std::make_unique<graphic::sphere>(vec3d{ 0, 0.3, window_position }, 0.5, 0.1, 0.4, 0.8));
        hittables.push_back(std::make_unique<graphic::sphere>(vec3d{ -1, -0.2, window_position - 3 }, 0.3, 0.4, 0.8, 0.1));
        hittables.push_back(std::make_unique<graphic::sphere>(vec3d{ 0, -100.5, window_position - 1 }, 100, 0.8, 0.1, 0.1));

        graphic::hittable_list world(std::move(hittables));

        for (int j = ny - 1; j >= 0; --j) {
            for (int i = 0; i < nx; ++i) {
                const dim_t v = dim_t(j) / dim_t(ny);
                const dim_t u = dim_t(i) / dim_t(nx);
                const graphic::ray ray = cam.get_ray(u, v);
                const graphic::color color = to_color(ray, world);
                out << color << "\n";
            }
        }
        out.close();
    }
}
