#pragma once

#include <cmath>
#include <type_traits>

namespace geometry {

using dim_t = double;

struct vec3d {
    dim_t x, y, z;
    vec3d& operator+=(const vec3d& v) noexcept {
        x += v.x;
        y += v.y;
        z += v.z;
        return *this;
    }
    vec3d& operator-=(const vec3d& v) noexcept {
        x -= v.x;
        y -= v.y;
        z -= v.z;
        return *this;
    }
    vec3d& operator*=(dim_t s) noexcept {
        x *= s;
        y *= s;
        z *= s;
        return *this;
    }
    vec3d& operator/=(dim_t s) noexcept {
        x /= s;
        y /= s;
        z /= s;
        return *this;
    }
};

static_assert(std::is_pod<vec3d>::value);

constexpr bool operator==(const vec3d& u, const vec3d& v) noexcept {
    return u.x == v.x && u.y == v.y && u.z == v.z;
}

constexpr bool operator!=(const vec3d& u, const vec3d& v) noexcept {
    return not(u == v);
}

constexpr vec3d operator-(const vec3d& v) noexcept {
    return vec3d{ -v.x, -v.y, -v.z };
}

constexpr vec3d operator+(const vec3d& u, const vec3d& v) noexcept {
    return vec3d{ u.x + v.x, u.y + v.y, u.z + v.z };
}

constexpr vec3d operator-(const vec3d& u, const vec3d& v) noexcept {
    return vec3d{ u.x - v.x, u.y - v.y, u.z - v.z };
}

constexpr vec3d operator*(const vec3d& v, dim_t s) noexcept {
    return vec3d{ v.x * s, v.y * s, v.z * s };
}

constexpr vec3d operator*(dim_t s, const vec3d& v) noexcept {
    return v * s;
}

constexpr vec3d operator/(const vec3d& v, dim_t s) noexcept {
    return vec3d{ v.x / s, v.y / s, v.z / s };
}

constexpr dim_t dot(const vec3d& u, const vec3d& v) noexcept {
    return u.x * v.x + u.y * v.y + u.z * v.z;
}

constexpr vec3d cross(const vec3d& u, const vec3d& v) noexcept {
    return { u.y * v.z - u.z * v.y,
        u.z * v.x - u.x * v.z,
        u.x * v.y - u.y * v.x };
}

constexpr dim_t size_square(const vec3d& v) noexcept {
    return dot(v, v);
}

inline dim_t size(const vec3d& v) noexcept {
    return std::sqrt(size_square(v));
}

inline vec3d unity(const vec3d& v) noexcept {
    return v / size(v);
}
}
