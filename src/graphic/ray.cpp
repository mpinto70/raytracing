#include "ray.h"

namespace graphic {
ray::ray(const geometry::vec3d& origin, const geometry::vec3d& direction) noexcept
      : origin_(origin), direction_(geometry::unity(direction)) {
}

}
