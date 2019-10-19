#include "random.h"

namespace graphic {
std::uniform_real_distribution<double> Random::distribution(0.0, 1.0);
std::mt19937 Random::generator;
std::function<double()> Random::rand_generator = std::bind(distribution, generator);
}
