#include "hittable.h"

#include <memory>
#include <vector>

namespace graphic {
class hittable_list {
public:
    explicit hittable_list(std::vector<std::unique_ptr<hittable>> list);
    bool hit(const ray& r, float t_min, float t_max, hit_record& record) const;

private:
    std::vector<std::unique_ptr<hittable>> list_;
};
}