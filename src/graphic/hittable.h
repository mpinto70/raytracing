#pragma once

#include "color.h"
#include "ray.h"

#include <type_traits>

namespace graphic {

struct hit_record {
    dim_t t;
    geometry::vec3d p;
    geometry::vec3d normal;
};

static_assert(std::is_pod<hit_record>::value);

class hittable {
public:
    virtual ~hittable() noexcept = default;
    virtual bool hit(const ray& r, dim_t t_min, dim_t t_max, hit_record& record) const noexcept = 0;
    [[nodiscard]] virtual std::optional<ray> bounce(const ray& r, const hit_record& record) const noexcept = 0;
    [[nodiscard]] virtual color dim(color c) const noexcept = 0;
};

}
