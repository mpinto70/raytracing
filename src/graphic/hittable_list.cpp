#include "hittable_list.h"

namespace graphic {
hittable_list::hittable_list(std::vector<std::unique_ptr<hittable>> list) noexcept
      : list_(std::move(list)) {
}

bool hittable_list::hit(const ray& r, float t_min, float t_max, hit_record& record) const noexcept {
    hit_record temp_rec{};
    bool hit_anything = false;
    float closest_so_far = t_max;
    for (const auto& hittable_ptr : list_) {
        if (hittable_ptr->hit(r, t_min, closest_so_far, temp_rec)) {
            hit_anything = true;
            closest_so_far = temp_rec.t;
            record = temp_rec;
        }
    }

    return hit_anything;
}

}
