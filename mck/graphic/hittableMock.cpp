#include "hittableMock.h"

namespace graphic {
bool operator==(const hit_record& lhs, const hit_record& rhs) {
    return lhs.t == rhs.t && lhs.normal == rhs.normal && lhs.p == rhs.p;
}
bool operator==(const ray& lhs, const ray& rhs) {
    return lhs.origin == rhs.origin && lhs.direction == rhs.direction;
}

namespace mck {

hittable_mock::hittable_mock() = default;
hittable_mock::~hittable_mock() noexcept = default;
}
}
