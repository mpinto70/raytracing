#pragma once

#include "geometry/vec3d.h"

#include <type_traits>

namespace graphic {

class ray {
public:
    ray(const geometry::vec3d& origin, const geometry::vec3d& direction) noexcept;

    [[nodiscard]] const geometry::vec3d& origin() const noexcept { return origin_; }
    [[nodiscard]] const geometry::vec3d& direction() const noexcept { return direction_; }

    [[nodiscard]] geometry::vec3d point_at_parameter(float t) const noexcept {
        return origin_ + t * direction_;
    }

private:
    geometry::vec3d origin_;
    geometry::vec3d direction_;
};

}
