#pragma once

#include "graphic/ray.h"

#include <type_traits>

namespace graphic {

struct hit_record {
    float t;
    geometry::vec3d p;
    geometry::vec3d normal;
};

static_assert(std::is_pod<hit_record>::value);

class hittable {
public:
    virtual ~hittable() noexcept = default;
    virtual bool hit(const ray& r, float t_min, float t_max, hit_record& record) const = 0;
};

}
