#pragma once

#include "graphic/hittable.h"

#include <type_traits>

namespace graphic {

class sphere : public hittable {
public:
    sphere(geometry::vec3d center, float radius);
    ~sphere() noexcept override = default;

    [[nodiscard]] const geometry::vec3d& center() const { return center_; }
    [[nodiscard]] float radius() const { return radius_; }

    bool hit(const ray& r, float t_min, float t_max, hit_record& record) const override;

private:
    geometry::vec3d center_;
    float radius_;
};

}
