#pragma once

#include <functional>
#include <random>

namespace graphic {
class Random {
private:
    static std::uniform_real_distribution<double> distribution;
    static std::mt19937 generator;
    static std::function<double()> rand_generator;

public:
    static double next() {
        return rand_generator();
    }
};
}
