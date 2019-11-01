#pragma once

#include "hittable.h"

#include <type_traits>

namespace graphic {

class sphere_transparent : public hittable {
public:
    sphere_transparent(const geometry::vec3d& center, dim_t radius, dim_t refractive_index, dim_t dim_r, dim_t dim_g, dim_t dim_b) noexcept;
    ~sphere_transparent() noexcept override = default;

    [[nodiscard]] const geometry::vec3d& center() const noexcept { return center_; }
    [[nodiscard]] dim_t radius() const noexcept { return radius_; }
    [[nodiscard]] dim_t dim_r() const noexcept { return dim_r_; }
    [[nodiscard]] dim_t dim_g() const noexcept { return dim_g_; }
    [[nodiscard]] dim_t dim_b() const noexcept { return dim_b_; }

    bool hit(const ray& r, dim_t t_min, dim_t t_max, hit_record& record) const noexcept override;
    [[nodiscard]] std::optional<ray> bounce(const ray& r, const hit_record& record) const noexcept override;
    [[nodiscard]] color dim(color c) const noexcept override;

private:
    geometry::vec3d center_;
    dim_t radius_;
    dim_t dim_r_;
    dim_t dim_g_;
    dim_t dim_b_;
    dim_t r_inwards_;  ///< r = n_air / n_sphere (n_air == 1)
    dim_t r_outwards_; ///< r = n_sphere / n_air (n_air == 1)
};

}
