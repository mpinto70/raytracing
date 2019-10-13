#pragma once

#include <type_traits>

namespace graphic {

struct color {
    int r, g, b;
};

static_assert(std::is_pod<color>::value);

}
