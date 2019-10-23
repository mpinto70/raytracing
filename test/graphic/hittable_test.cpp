#include "geometry/vec3d.h"
#include "graphic/hittable.h"

#include "../mck/graphic/hittable_mock.h"

#include <gtest/gtest.h>

namespace graphic {

namespace {
constexpr geometry::vec3d p1{ 1, 2, 3 };
constexpr geometry::vec3d n1{ 7, 4, 3 };
constexpr hit_record h1{ 127.0f, p1, n1 };
constexpr geometry::vec3d p2{ -3, 2, -9 };
constexpr geometry::vec3d n2{ -13, 1, 0 };
constexpr hit_record h2{ -4.0f, p2, n2 };
}

TEST(hit_record, creation) {
    static_assert(h1.t == 127.0f);
    static_assert(h1.p == p1);
    static_assert(h1.normal == n1);
    static_assert(h2.t == -4.0f);
    static_assert(h2.p == p2);
    static_assert(h2.normal == n2);
}

using ::testing::Return;
using ::testing::StrictMock;
TEST(hittable, hit) {
    mck::hittable_mock hittable_mock({ true, false });

    hit_record record = { -3.0f, p1, n1 };
    const ray r{ p2, n2 };
    EXPECT_TRUE(hittable_mock.hit(r, -10.0f, 15.0f, record));
    EXPECT_EQ(hittable_mock.num_calls, 1u);
    EXPECT_FALSE(hittable_mock.hit(r, -10.0f, 15.0f, record));
    EXPECT_EQ(hittable_mock.num_calls, 2u);
}
}
