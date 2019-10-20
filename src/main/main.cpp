#include "geometry/vec3d.h"
#include "graphic/camera.h"
#include "graphic/color.h"
#include "graphic/hittable_list.h"
#include "graphic/random.h"
#include "graphic/ray.h"
#include "graphic/sphere.h"

#include <cmath>
#include <fstream>
#include <iostream>
#include <memory>
#include <unistd.h>

using geometry::dim_t;
namespace graphic {
std::ostream& operator<<(std::ostream& out, const color& cr) noexcept {
    out << cr.r << " " << cr.g << " " << cr.b;
    return out;
}
}

namespace {
geometry::vec3d random_in_unit_sphere() {
    using geometry::vec3d;
    using graphic::Random;
    for (;;) {
        const vec3d p = 2 * vec3d{ Random::next(), Random::next(), Random::next() } - vec3d{ 1, 1, 1 };
        if (size_square(p) < 1.0)
            return p;
    }
}

graphic::color to_color(const graphic::ray& ray, const graphic::hittable_list& world) noexcept {
    using geometry::vec3d;
    using graphic::color;
    using graphic::hit_record;
    hit_record rec{};
    if (world.hit(ray, 0.0, dim_t(15000000.0), rec)) {
        const vec3d target = rec.p + rec.normal + random_in_unit_sphere();
        return 0.5 * to_color(graphic::ray(rec.p, target - rec.p), world);
    } else {
        return color{0xff, 0xa5, 0x00};
    }
}
}

int main() {
    using geometry::vec3d;

    constexpr int nx = 2000;
    constexpr int ny = 1000;
    constexpr int ns = 10;
    constexpr auto window_position = dim_t(-1.0);
    constexpr auto camera_position = dim_t(1.0);

    constexpr vec3d lower_left_corner = { dim_t(-2.0), dim_t(-1.0), window_position };
    constexpr vec3d origin = { dim_t(0.0), dim_t(0.0), camera_position };
    graphic::camera cam(origin, lower_left_corner, 4, 2);
    for (int p = 0; p <= 0; ++p) {
        std::cerr << p << "\n";
        std::ofstream out("/home/marcelo/tmp/img-" + std::to_string(p + 3) + ".ppm");
        out << "P3\n"
            << nx << " " << ny << "\n255\n";
        std::vector<std::unique_ptr<graphic::hittable>> hittables;
        hittables.push_back(std::make_unique<graphic::sphere>(vec3d{ 0, 0, window_position }, 0.5));
        hittables.push_back(std::make_unique<graphic::sphere>(vec3d{ 0, -100.5, -1 }, 100));

        graphic::hittable_list world(std::move(hittables));

        for (int j = ny - 1; j >= 0; --j) {
            for (int i = 0; i < nx; ++i) {
                int r = 0, g = 0, b = 0;
                for (int s = 0; s < ns; ++s) {
                    const dim_t v = (dim_t(j) + graphic::Random::next()) / dim_t(ny);
                    const dim_t u = (dim_t(i) + graphic::Random::next()) / dim_t(nx);
                    const graphic::ray ray = cam.get_ray(u, v);
                    const graphic::color color = to_color(ray, world);
                    r += color.r;
                    g += color.g;
                    b += color.b;
                }
                const graphic::color px_color{ r / ns, g / ns, b / ns };
                out << px_color << "\n";
            }
        }
        out.close();
    }
}
