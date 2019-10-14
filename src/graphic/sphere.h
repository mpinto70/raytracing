#pragma once

#include "graphic/hittable.h"

#include <type_traits>

namespace graphic {

class sphere : public hittable {
public:
    sphere(geometry::vec3d center, float radius) noexcept;
    ~sphere() noexcept override = default;

    [[nodiscard]] const geometry::vec3d& center() const noexcept { return center_; }
    [[nodiscard]] float radius() const noexcept { return radius_; }

    bool hit(const ray& r, float t_min, float t_max, hit_record& record) const noexcept override;

private:
    geometry::vec3d center_;
    float radius_;
};

}
