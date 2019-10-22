#include "hittable_list.h"

namespace graphic {
hittable_list::hittable_list(std::vector<std::unique_ptr<hittable>> list) noexcept
      : list_(std::move(list)) {
}

std::optional<std::reference_wrapper<const hittable>> hittable_list::hit(const ray& r, dim_t t_min, dim_t t_max, hit_record& record) const noexcept {
    hit_record temp_rec{};
    dim_t closest_so_far = t_max;
    const hittable* member_hit = nullptr;
    for (const auto& hittable_ptr : list_) {
        if (hittable_ptr->hit(r, t_min, closest_so_far, temp_rec)) {
            member_hit = hittable_ptr.get();
            closest_so_far = temp_rec.t;
            record = temp_rec;
        }
    }

    if (member_hit != nullptr) {
        return *member_hit;
    }

    return std::nullopt;
}

}
