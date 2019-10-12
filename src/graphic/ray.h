#pragma once

#include "geometry/vec3d.h"

#include <cmath>
#include <type_traits>

namespace graphic {

struct ray {
    geometry::vec3d origin;
    geometry::vec3d direction;
    [[nodiscard]] constexpr geometry::vec3d point_at_parameter(float t) const {
        return origin + t * direction;
    }
};

static_assert(std::is_pod<ray>::value);

}
