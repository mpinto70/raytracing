#pragma once

#include "graphic/ray.h"

namespace graphic {
class camera {
public:
    camera(const geometry::vec3d& origin, const geometry::vec3d& lower_left_corner, dim_t width, dim_t height);
    [[nodiscard]] ray get_ray(dim_t u, dim_t v) const {
        return ray(origin_, lower_left_corner_ + u * horizontal_ + v * vertical_ - origin_);
    }
private:
    geometry::vec3d origin_;
    geometry::vec3d lower_left_corner_;
    geometry::vec3d horizontal_;
    geometry::vec3d vertical_;

};
}
