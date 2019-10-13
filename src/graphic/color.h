#pragma once

#include <algorithm>
#include <type_traits>

namespace graphic {

struct color {
    int r, g, b;
    color& operator+=(const color& v) noexcept {
        r += v.r;
        g += v.g;
        b += v.b;
        return *this;
    }
    color& operator-=(const color& v) noexcept {
        r -= v.r;
        g -= v.g;
        b -= v.b;
        return *this;
    }
    color& operator*=(float s) noexcept {
        r = std::max(std::min(int(r * s), 255), 0);
        g = std::max(std::min(int(g * s), 255), 0);
        b = std::max(std::min(int(b * s), 255), 0);
        return *this;
    }
    color& operator/=(float s) noexcept {
        r = std::max(std::min(int(r / s), 255), 0);
        g = std::max(std::min(int(g / s), 255), 0);
        b = std::max(std::min(int(b / s), 255), 0);
        return *this;
    }
};

static_assert(std::is_pod<color>::value);

color operator+(color u, const color& v) noexcept {
    u += v;
    return u;
}

color operator-(color u, const color& v) noexcept {
    u -= v;
    return u;
}

color operator*(color v, float s) noexcept {
    v *= s;
    return v;
}

color operator*(float s, const color& v) noexcept {
    return v * s;
}

color operator/(color v, float s) noexcept {
    v /= s;
    return v;
}

}
