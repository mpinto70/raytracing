#pragma once

#include "graphic/hittable.h"

#include <gmock/gmock.h>

namespace graphic {
bool operator==(const hit_record& lhs, const hit_record& rhs);
bool operator==(const ray& lhs, const ray& rhs);
namespace mck {
class hittable_mock : public hittable {
public:
    explicit hittable_mock(bool res);
    template <size_t N>
    explicit hittable_mock(const bool (&res)[N])
          : num_calls(0), results(res, res + N) {
    }
    ~hittable_mock() noexcept override;

    bool hit(const ray& r, float t_min, float t_max, hit_record& record) const noexcept override;
    mutable size_t num_calls;
    std::vector<int> results;
};
}
}
