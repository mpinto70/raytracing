#include "hittableMock.h"

namespace graphic {
bool operator==(const hit_record& lhs, const hit_record& rhs) {
    return lhs.t == rhs.t && lhs.normal == rhs.normal && lhs.p == rhs.p;
}
bool operator==(const ray& lhs, const ray& rhs) {
    return lhs.origin() == rhs.origin() && lhs.direction() == rhs.direction();
}

namespace mck {
hittable_mock::hittable_mock(bool res)
      : num_calls(0), results(1, res) {
}

hittable_mock::~hittable_mock() noexcept {
    EXPECT_EQ(num_calls, results.size());
}

bool hittable_mock::hit(const ray&, dim_t, dim_t, hit_record&) const noexcept {
    const auto index = num_calls;
    ++num_calls;
    EXPECT_LT(index, results.size());
    if (index >= results.size()) {
        return false;
    }
    return results[index];
}

std::optional<ray> hittable_mock::bounce(const ray&, const hit_record&) const noexcept {
    return std::nullopt;
}

}
}
