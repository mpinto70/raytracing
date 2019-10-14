#include "graphic/sphere.h"

#include <gtest/gtest.h>

namespace graphic {

using geometry::vec3d;

TEST(sphere, creation) {
    constexpr vec3d C1{ 7, 8, 9 };
    constexpr float R1 = 5.0f;
    const sphere S1{ C1, R1 };
    constexpr vec3d C2{ -2, 3, 10 };
    constexpr float R2 = 3.4f;
    const sphere S2{ C2, R2 };

    EXPECT_EQ(S1.center(), C1);
    EXPECT_EQ(S1.radius(), R1);
    EXPECT_EQ(S2.center(), C2);
    EXPECT_EQ(S2.radius(), R2);
}

TEST(sphere, hit_simple_and_direct) {
    hit_record record{};
    constexpr vec3d C{ 0, 0, -30 };
    constexpr float R = 5.0f;
    const ray r{ { 0, 0, 0 }, { 0, 0, -1 } };
    const sphere s(C, R);
    constexpr vec3d hit_point{ 0, 0, -25 };
    constexpr vec3d normal{ 0, 0, 1 };

    EXPECT_TRUE(s.hit(r, 0.0, 500, record));
    EXPECT_EQ(record.t, 25.0f);
    EXPECT_EQ(record.p, hit_point);
    EXPECT_EQ(record.normal, normal);
}

TEST(sphere, hit_out_of_range) {
    hit_record record{};
    constexpr vec3d C{ 0, 0, -30 };
    constexpr float R = 5.0f;
    const ray r{ { 0, 0, 0 }, { 0, 0, -1 } };
    const sphere s(C, R);

    EXPECT_FALSE(s.hit(r, 35.5f, 500, record));
}

}
