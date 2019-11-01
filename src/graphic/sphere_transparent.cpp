#include "sphere_transparent.h"

namespace graphic {
namespace {
void set_record(const ray& r, dim_t t, hit_record& record, const geometry::vec3d& center, dim_t radius) {
    record.t = t;
    record.p = r.point_at_parameter(t);
    record.normal = (record.p - center) / radius;
}

}

sphere_transparent::sphere_transparent(const geometry::vec3d& center,
      dim_t radius,
      dim_t refractive_index,
      dim_t dim_r,
      dim_t dim_g,
      dim_t dim_b) noexcept
      : center_(center),
        radius_(radius),
        dim_r_(dim_r),
        dim_g_(dim_g),
        dim_b_(dim_b),
        r_inwards_(1.0 / refractive_index),
        r_outwards_(refractive_index) {
}

bool sphere_transparent::hit(const ray& r, dim_t t_min, dim_t t_max, hit_record& record) const noexcept {
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

std::optional<ray> sphere_transparent::bounce(const ray& r, const hit_record& record) const noexcept {
    const auto& l = r.direction();
    const auto nl = dot(l, record.normal);
    const auto n = (nl < 0) ? record.normal : -record.normal;
    const dim_t C = (nl > 0) ? nl : -nl;
    const dim_t R = (nl < 0.0) ? r_inwards_ : r_outwards_;
    const dim_t RR = R * R;
    const dim_t RC = R * C;
    const dim_t RCRC = RC * RC;

    const dim_t radicand = 1 - RR + RCRC;

    if (radicand < 0) { // total reflexion
        const auto direction = reflection_direction(r.direction(), n);
        if (direction)
            return ray(record.p, *direction);
        return std::nullopt;
    } else {
        const auto direction = R * l + (RC - std::sqrt(radicand)) * n;
        if (size_square(direction) > 0.001)
            return ray(record.p, direction);
        return std::nullopt;
    }
}

color sphere_transparent::dim(color c) const noexcept {
    c.r *= dim_r_;
    c.g *= dim_g_;
    c.b *= dim_b_;

    return c;
}

}
