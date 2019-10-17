#include "geometry/vec3d.h"

#include <gtest/gtest.h>

namespace geometry {

constexpr vec3d U{ 7, 8, 9 };
constexpr vec3d V{ 1, 2, 4 };
constexpr vec3d I{ 1, 0, 0 };
constexpr vec3d J{ 0, 1, 0 };
constexpr vec3d K{ 0, 0, 1 };

TEST(vec3d, creation) {
    static_assert(U.x == 7);
    static_assert(U.y == 8);
    static_assert(U.z == 9);

    static_assert(V.x == 1);
    static_assert(V.y == 2);
    static_assert(V.z == 4);

    static_assert(V != U);
    static_assert(U == U);
    static_assert(V == V);
}

TEST(vec3d, negation) {
    static_assert(-U == vec3d{ -7, -8, -9 });
    static_assert(-V == vec3d{ -1, -2, -4 });
}

TEST(vec3d, add) {
    static_assert(U + V == vec3d{ 8, 10, 13 });
    static_assert(V + U == vec3d{ 8, 10, 13 });

    vec3d w = U;
    w += V;
    EXPECT_EQ(w, U + V);
}

TEST(vec3d, subtract) {
    static_assert(U - V == vec3d{ 6, 6, 5 });
    static_assert(V - U == vec3d{ -6, -6, -5 });

    vec3d w = U;
    w -= V;
    EXPECT_EQ(w, U - V);
}

TEST(vec3d, scalar) {
    static_assert(I * 3 == vec3d{ 3, 0, 0 });
    static_assert(U * 7 == vec3d{ 49, 56, 63 });

    static_assert(3 * I == vec3d{ 3, 0, 0 });
    static_assert(7 * U == vec3d{ 49, 56, 63 });

    static_assert(I / 2 == vec3d{ 0.5, 0, 0 });
    static_assert(V / 2 == vec3d{ 0.5, 1, 2 });
}

TEST(vec3d, dot) {
    static_assert(dot(V, I) == 1);
    static_assert(dot(V, J) == 2);
    static_assert(dot(V, K) == 4);

    static_assert(dot(U, V) == 59);
    static_assert(dot(I, J) == 0);
    static_assert(dot(I, K) == 0);
    static_assert(dot(J, K) == 0);
}

TEST(vec3d, cross) {
    constexpr vec3d zero{ 0, 0, 0 };
    static_assert(cross(I, I) == zero);
    static_assert(cross(J, J) == zero);
    static_assert(cross(K, K) == zero);
    static_assert(cross(U, U) == zero);
    static_assert(cross(V, V) == zero);

    static_assert(cross(I, J) == K);
    static_assert(cross(J, K) == I);
    static_assert(cross(K, I) == J);

    static_assert(cross(J, I) == -K);
    static_assert(cross(K, J) == -I);
    static_assert(cross(I, K) == -J);

    constexpr vec3d UV{ 14, -19, 6 };
    static_assert(cross(U, V) == UV);
    static_assert(cross(V, U) == -UV);
}

TEST(vec3d, size_square) {
    constexpr vec3d zero{ 0, 0, 0 };
    static_assert(size_square(zero) == 0);
    static_assert(size_square(I) == 1);
    static_assert(size_square(J) == 1);
    static_assert(size_square(K) == 1);

    static_assert(size_square(U) == 194);
    static_assert(size_square(V) == 21);
}

TEST(vec3d, size) {
    constexpr vec3d zero{ 0, 0, 0 };
    EXPECT_EQ(size(zero), 0);
    EXPECT_EQ(size(I), 1);
    EXPECT_EQ(size(J), 1);
    EXPECT_EQ(size(K), 1);

    EXPECT_EQ(size(U), std::sqrt(dim_t(194)));
    EXPECT_EQ(size(V), std::sqrt(dim_t(21)));
}

TEST(vec3d, unity) {
    EXPECT_EQ(unity(I), I);
    EXPECT_EQ(unity(J), J);
    EXPECT_EQ(unity(K), K);

    EXPECT_EQ(unity(U), U / std::sqrt(dim_t(194)));
    EXPECT_EQ(unity(V), V / std::sqrt(dim_t(21)));
}
}
