#include "sphere.h"

namespace graphic {
sphere::sphere(geometry::vec3d center, float radius)
      : center_(center), radius_(radius) {
}

bool sphere::hit(const ray& r, float t_min, float t_max, hit_record& record) const {
    using geometry::vec3d;

    const vec3d oc = r.origin - center_;
    const float a = dot(r.direction, r.direction);
    const float b = 2.0f * dot(oc, r.direction);
    const float c = dot(oc, oc) - radius_ * radius_;
    const float discriminant = b * b - 4 * a * c;
    if (discriminant > 0) {
        float t = (-b - std::sqrt(discriminant)) / (2.0f * a);
        if (t > t_min && t < t_max) {
            record.t = t;
            record.p = r.point_at_parameter(t);
            record.normal = (record.p - center_) / radius_;
            return true;
        }
        t = (-b + std::sqrt(discriminant)) / (2.0f * a);
        if (t > t_min && t < t_max) {
            record.t = t;
            record.p = r.point_at_parameter(t);
            record.normal = (record.p - center_) / radius_;
            return true;
        }
    }
    return false;
}
}
