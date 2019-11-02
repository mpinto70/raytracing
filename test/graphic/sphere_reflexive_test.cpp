#include "graphic/sphere_reflexive.h"

#include <gtest/gtest.h>

namespace graphic {

using geometry::vec3d;

TEST(sphere_reflexive, creation) {
    constexpr vec3d C1{ 7, 8, 9 };
    constexpr dim_t R1 = 5.0f;
    const sphere_reflexive S1{ C1, R1, 0.1, 0.2, 0.3 };
    constexpr vec3d C2{ -2, 3, 10 };
    constexpr dim_t R2 = 3.4f;
    const sphere_reflexive S2{ C2, R2, 0.4, 0.5, 0.7 };

    EXPECT_EQ(S1.center(), C1);
    EXPECT_EQ(S1.radius(), R1);
    EXPECT_EQ(S1.dim_r(), dim_t(0.1));
    EXPECT_EQ(S1.dim_g(), dim_t(0.2));
    EXPECT_EQ(S1.dim_b(), dim_t(0.3));
    EXPECT_EQ(S2.center(), C2);
    EXPECT_EQ(S2.radius(), R2);
    EXPECT_EQ(S2.dim_r(), dim_t(0.4));
    EXPECT_EQ(S2.dim_g(), dim_t(0.5));
    EXPECT_EQ(S2.dim_b(), dim_t(0.7));
}

TEST(sphere_reflexive, hit_simple_and_direct) {
    hit_record record{};
    constexpr vec3d C{ 0, 0, -30 };
    constexpr dim_t R = 5.0f;
    const ray r{ { 0, 0, 0 }, { 0, 0, -1 } };
    const sphere_reflexive s(C, R, 0.1, 0.2, 0.3);
    constexpr vec3d hit_point{ 0, 0, -25 };
    constexpr vec3d normal{ 0, 0, 1 };

    EXPECT_TRUE(s.hit(r, 0.0, 500, record));
    EXPECT_EQ(record.t, 25.0f);
    EXPECT_EQ(record.p, hit_point);
    EXPECT_EQ(record.normal, normal);
}

TEST(sphere_reflexive, hit_out_of_range) {
    hit_record record{};
    constexpr vec3d C{ 0, 0, -30 };
    constexpr dim_t R = 5.0f;
    const ray r{ { 0, 0, 0 }, { 0, 0, -1 } };
    const sphere_reflexive s(C, R, 0.1, 0.2, 0.3);

    EXPECT_FALSE(s.hit(r, 35.5f, 500, record));
}

TEST(sphere_reflexive, bounce) {
    const hit_record record{ 1.3, { 1, 2, 3 }, { 2, 3, 4 } };
    constexpr vec3d C{ 0, 0, -30 };
    constexpr dim_t R = 5.0f;
    const ray r{ { 0, 0, 0 }, { -7, -2, -1 } };
    const sphere_reflexive s(C, R, 0.1, 0.2, 0.3);

    auto out_ray = s.bounce(r, record);

    ASSERT_TRUE(out_ray);
    EXPECT_EQ(out_ray->origin(), record.p);
    const auto direction_option = reflection_direction(r.direction(), record.normal);
    ASSERT_TRUE(direction_option);
    const auto direction = unity(*direction_option);
    EXPECT_EQ(out_ray->direction(), direction);
}

TEST(sphere_reflexive, dim) {
    constexpr vec3d C{ 0, 0, -30 };
    constexpr dim_t R = 5.0f;
    const ray r{ { 0, 0, 0 }, { -7, -2, -1 } };
    const sphere_reflexive s(C, R, 0.1, 0.2, 0.3);

    auto out_color = s.dim(color{ 234, 123, 210 });
    constexpr color expected_color = { 23, 24, 63 };

    EXPECT_EQ(out_color.r, expected_color.r);
    EXPECT_EQ(out_color.g, expected_color.g);
    EXPECT_EQ(out_color.b, expected_color.b);
}
}
