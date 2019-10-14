#include "graphic/ray.h"

#include <gtest/gtest.h>

namespace graphic {

using geometry::vec3d;

namespace {
constexpr vec3d U{ 7, 8, 9 };
constexpr vec3d V{ 1, 2, 4 };
constexpr vec3d I{ 1, 0, 0 };
constexpr vec3d J{ 0, 1, 0 };
constexpr ray R1{ U, I };
constexpr ray R2{ V, J };
}

TEST(ray, creation) {
    static_assert(R1.origin == U);
    static_assert(R1.direction == I);
    static_assert(R2.origin == V);
    static_assert(R2.direction == J);
}

TEST(ray, point_at_parameter) {
    static_assert(R1.point_at_parameter(2.3f) == U + 2.3f * I);
    static_assert(R2.point_at_parameter(-3.2f) == V + -3.2f * J);
}
}
