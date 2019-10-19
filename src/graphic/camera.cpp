#include "camera.h"

namespace graphic {
camera::camera(const geometry::vec3d& origin, const geometry::vec3d& lower_left_corner, dim_t width, dim_t height)
      : origin_(origin), lower_left_corner_(lower_left_corner), horizontal_{ width, 0, 0 }, vertical_{ 0, height, 0 } {
}

}
