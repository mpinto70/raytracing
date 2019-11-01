#include "graphic/sphere_transparent.h"

#include <gtest/gtest.h>

namespace graphic {

using geometry::vec3d;

TEST(sphere_transparent, creation) {
    constexpr vec3d C1{ 7, 8, 9 };
    constexpr dim_t R1 = 5.0f;
    const sphere_transparent S1{ C1, R1, 1.458, 0.1, 0.2, 0.3 };
    constexpr vec3d C2{ -2, 3, 10 };
    constexpr dim_t R2 = 3.4f;
    const sphere_transparent S2{ C2, R2, 1.458, 0.4, 0.5, 0.7 };

    EXPECT_EQ(S1.center(), C1);
    EXPECT_EQ(S1.radius(), R1);
    EXPECT_EQ(S1.dim_r(), 0.1);
    EXPECT_EQ(S1.dim_g(), 0.2);
    EXPECT_EQ(S1.dim_b(), 0.3);
    EXPECT_EQ(S2.center(), C2);
    EXPECT_EQ(S2.radius(), R2);
    EXPECT_EQ(S2.dim_r(), 0.4);
    EXPECT_EQ(S2.dim_g(), 0.5);
    EXPECT_EQ(S2.dim_b(), 0.7);
}

TEST(sphere_transparent, hit_simple_and_direct) {
    hit_record record{};
    constexpr vec3d C{ 0, 0, -30 };
    constexpr dim_t R = 5.0f;
    const ray r{ { 0, 0, 0 }, { 0, 0, -1 } };
    const sphere_transparent s(C, R, 1.458, 0.1, 0.2, 0.3);
    constexpr vec3d hit_point{ 0, 0, -25 };
    constexpr vec3d normal{ 0, 0, 1 };

    EXPECT_TRUE(s.hit(r, 0.0, 500, record));
    EXPECT_EQ(record.t, 25.0f);
    EXPECT_EQ(record.p, hit_point);
    EXPECT_EQ(record.normal, normal);
}

TEST(sphere_transparent, hit_out_of_range) {
    hit_record record{};
    constexpr vec3d C{ 0, 0, -30 };
    constexpr dim_t R = 5.0f;
    const ray r{ { 0, 0, 0 }, { 0, 0, -1 } };
    const sphere_transparent s(C, R, 1.458, 0.1, 0.2, 0.3);

    EXPECT_FALSE(s.hit(r, 35.5f, 500, record));
}

TEST(sphere_transparent, bounce_front_middle) {
    constexpr vec3d C{ 0, 0, -30 };
    constexpr dim_t R = 5.0f;
    const ray r1{ { 0, 0, 0 }, { 0, 0, -1 } };
    const sphere_transparent s(C, R, 1.458, 0.9, 0.9, 0.9);
    hit_record record;
    ASSERT_TRUE(s.hit(r1, 0.001, 1500000, record));

    const auto r2 = s.bounce(r1, record);
    ASSERT_TRUE(r2);
    constexpr vec3d hit_p1{ 0, 0, -25 };
    constexpr vec3d dir_p1{ 0, 0, -1 };
    EXPECT_EQ(r2->origin(), hit_p1);
    EXPECT_EQ(r2->direction(), dir_p1);

    ASSERT_TRUE(s.hit(*r2, 0.001, 1500000, record));

    const auto r3 = s.bounce(r1, record);
    ASSERT_TRUE(r3);
    constexpr vec3d hit_p2{ 0, 0, -35 };
    constexpr vec3d dir_p2{ 0, 0, -1 };
    EXPECT_EQ(r3->origin(), hit_p2);
    EXPECT_EQ(r3->direction(), dir_p2);
}

TEST(sphere_transparent, bounce_off_center) {
    constexpr vec3d C{ 0, 0, -30 };
    constexpr dim_t R = 5.0f;
    const ray r1{ { 1, 1, 0 }, { 0, 0, -1 } };
    const sphere_transparent s(C, R, 1.458, 0.9, 0.9, 0.9);
    hit_record record;
    ASSERT_TRUE(s.hit(r1, 0.001, 1500000, record));

    const auto r2 = s.bounce(r1, record);
    ASSERT_TRUE(r2);
    constexpr vec3d hit_p1{ 1, 1, -25.204168 };
    constexpr vec3d normal_p1{ 0.19999998, 0.19999998, 0.9591663 };
    constexpr vec3d dir_p1{ -6.462767e-2, -6.462767e-2, -0.9958145 };
    EXPECT_FLOAT_EQ(record.normal.x, normal_p1.x);
    EXPECT_FLOAT_EQ(record.normal.y, normal_p1.y);
    EXPECT_FLOAT_EQ(record.normal.z, normal_p1.z);
    EXPECT_FLOAT_EQ(r2->origin().x, hit_p1.x);
    EXPECT_FLOAT_EQ(r2->origin().y, hit_p1.y);
    EXPECT_FLOAT_EQ(r2->origin().z, hit_p1.z);
    EXPECT_FLOAT_EQ(r2->direction().x, dir_p1.x);
    EXPECT_FLOAT_EQ(r2->direction().y, dir_p1.y);
    EXPECT_FLOAT_EQ(r2->direction().z, dir_p1.z);

    ASSERT_TRUE(s.hit(*r2, 0.001, 1500000, record));

    const auto r3 = s.bounce(*r2, record);
    ASSERT_TRUE(r3);
    constexpr vec3d hit_p2{ 0.366000692813, 0.366000692813, -34.9731369937 };
    constexpr vec3d normal_p2{ 7.32001318686e-2, 7.32001318686e-2, -0.994627307783 };
    constexpr vec3d dir_p2{ -0.128714342822, -0.128714342822, -0.983293056984 };
    EXPECT_FLOAT_EQ(r3->origin().x, hit_p2.x);
    EXPECT_FLOAT_EQ(r3->origin().y, hit_p2.y);
    EXPECT_FLOAT_EQ(r3->origin().z, hit_p2.z);
    EXPECT_FLOAT_EQ(record.normal.x, normal_p2.x);
    EXPECT_FLOAT_EQ(record.normal.y, normal_p2.y);
    EXPECT_FLOAT_EQ(record.normal.z, normal_p2.z);
    EXPECT_FLOAT_EQ(r3->direction().x, dir_p2.x);
    EXPECT_FLOAT_EQ(r3->direction().y, dir_p2.y);
    EXPECT_FLOAT_EQ(r3->direction().z, dir_p2.z);
}

TEST(sphere_transparent, dim) {
    constexpr vec3d C{ 0, 0, -30 };
    constexpr dim_t R = 5.0f;
    const ray r{ { 0, 0, 0 }, { -7, -2, -1 } };
    const sphere_transparent s(C, R, 1.458, 0.1, 0.2, 0.3);

    auto out_color = s.dim(color{ 234, 123, 210 });
    constexpr color expected_color = { 23, 24, 63 };

    EXPECT_EQ(out_color.r, expected_color.r);
    EXPECT_EQ(out_color.g, expected_color.g);
    EXPECT_EQ(out_color.b, expected_color.b);
}
}
