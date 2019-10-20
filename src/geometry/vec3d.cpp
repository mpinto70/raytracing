#include "vec3d.h"

namespace geometry {
vec3d reflection_direction(const vec3d& light_direction, const vec3d& normal_direction) {
    const dim_t normal_projection = -dot(light_direction, normal_direction);
    if (normal_projection < 0.0001) {
        return { 0, 0, 0 };
    }
    return 2.0 * normal_projection * normal_direction + light_direction;
}

}
