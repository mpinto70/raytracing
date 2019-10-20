#include "random.h"

namespace graphic {
std::uniform_real_distribution<dim_t> Random::distribution(0.0, 1.0);
std::mt19937 Random::generator;
std::function<dim_t()> Random::rand_generator = std::bind(distribution, generator);
}
