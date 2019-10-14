#include "graphic/hittable.h"
#include "geometry/vec3d.h"

#include "../mck/graphic/hittableMock.h"

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
    StrictMock<mck::hittable_mock> hittable_mock;
    hit_record record = { -3.0f, p1, n1 };
    constexpr ray r{ p2, n2 };
    constexpr float t_min = -10.0f;
    constexpr float t_max = 15.0f;

    EXPECT_CALL(hittable_mock, hit(r, t_min, t_max, record)).WillOnce(Return(true));
    hittable_mock.hit(r, -10.0f, 15.0f, record);
}
}