#include "graphic/color.h"

#include <gtest/gtest.h>

namespace graphic {

namespace {
constexpr color C1{ 127, 128, 255 };
constexpr color C2{ 0, 36, 48 };
}

TEST(color, creation) {
    static_assert(C1.r == 127);
    static_assert(C1.g == 128);
    static_assert(C1.b == 255);
    static_assert(C2.r == 0);
    static_assert(C2.g == 36);
    static_assert(C2.b == 48);
}
}
