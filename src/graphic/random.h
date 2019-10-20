#pragma once

#include "geometry/vec3d.h"

#include <functional>
#include <random>

namespace graphic {
using geometry::dim_t;

class Random {
private:
    static std::uniform_real_distribution<dim_t> distribution;
    static std::mt19937 generator;
    static std::function<dim_t()> rand_generator;

public:
    static dim_t next() {
        return rand_generator();
    }
};
}
