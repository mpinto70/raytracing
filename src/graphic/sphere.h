#pragma once

#include "graphic/hittable.h"

#include <type_traits>

namespace graphic {

class sphere : public hittable {
public:
    sphere(const geometry::vec3d& center, dim_t radius) noexcept;
    ~sphere() noexcept override = default;

    [[nodiscard]] const geometry::vec3d& center() const noexcept { return center_; }
    [[nodiscard]] dim_t radius() const noexcept { return radius_; }

    bool hit(const ray& r, dim_t t_min, dim_t t_max, hit_record& record) const noexcept override;
    std::optional<ray> bounce(const ray& r, const hit_record& record) const noexcept override;

private:
    geometry::vec3d center_;
    dim_t radius_;
};

}
