#include "hittable.h"

#include <memory>
#include <vector>

namespace graphic {
class hittable_list {
public:
    explicit hittable_list(std::vector<std::unique_ptr<hittable>> list) noexcept;
    std::optional<std::reference_wrapper<const hittable>> hit(const ray& r, dim_t t_min, dim_t t_max, hit_record& record) const noexcept;

private:
    std::vector<std::unique_ptr<hittable>> list_;
};
}
