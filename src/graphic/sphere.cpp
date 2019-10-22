#include "sphere.h"

namespace graphic {
namespace {
void set_record(const ray& r, dim_t t, hit_record& record, const geometry::vec3d& center, dim_t radius) {
    record.t = t;
    record.p = r.point_at_parameter(t);
    record.normal = (record.p - center) / radius;
}
}

sphere::sphere(const geometry::vec3d& center, dim_t radius) noexcept
      : center_(center), radius_(radius) {
}

bool sphere::hit(const ray& r, dim_t t_min, dim_t t_max, hit_record& record) const noexcept {
    using geometry::vec3d;

    const vec3d oc = r.origin() - center_;
    const dim_t a = dot(r.direction(), r.direction());
    const dim_t b = dim_t(2) * dot(oc, r.direction());
    const dim_t c = dot(oc, oc) - radius_ * radius_;
    const dim_t discriminant = b * b - 4 * a * c;
    if (discriminant >= 0) {
        const dim_t sqrt_discriminant = std::sqrt(discriminant);
        const dim_t two_a = dim_t(2) * a;
        dim_t t = (-b - sqrt_discriminant) / two_a;
        if (t > t_min && t < t_max) {
            set_record(r, t, record, center_, radius_);
            return true;
        }
        t = (-b + sqrt_discriminant) / two_a;
        if (t > t_min && t < t_max) {
            set_record(r, t, record, center_, radius_);
            return true;
        }
    }
    return false;
}

std::optional<ray> sphere::bounce(const ray& r, const hit_record& record) const noexcept {
    using geometry::vec3d;
    const auto target = reflection_direction(r.direction(), record.normal);
    if (target)
        return ray(record.p, *target);
    return std::nullopt;
}
}
