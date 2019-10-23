#pragma once

#include "hittable.h"

#include <type_traits>

namespace graphic {

class sphere_reflexive : public hittable {
public:
    sphere_reflexive(const geometry::vec3d& center, dim_t radius, dim_t dim_r, dim_t dim_g, dim_t dim_b) noexcept;
    ~sphere_reflexive() noexcept override = default;

    [[nodiscard]] const geometry::vec3d& center() const noexcept { return center_; }
    [[nodiscard]] dim_t radius() const noexcept { return radius_; }

    bool hit(const ray& r, dim_t t_min, dim_t t_max, hit_record& record) const noexcept override;
    [[nodiscard]] std::optional<ray> bounce(const ray& r, const hit_record& record) const noexcept override;
    [[nodiscard]] color dim(color c) const noexcept override;

private:
    geometry::vec3d center_;
    dim_t radius_;
    dim_t dim_r_;
    dim_t dim_g_;
    dim_t dim_b_;
};

}
