#include "geometry/vec3d.h"
#include "graphic/color.h"

#include <iostream>

namespace graphic {
std::ostream& operator<< (std::ostream& out, const color& cr) {
    out << cr.r << " " << cr.g << " " << cr.b;
    return out;
}
}

int main() {
    int nx = 200;
    int ny = 100;
    std::cout << "P3\n"
              << nx << " " << ny << "\n255\n";

    for (int j = ny - 1; j >= 0; j--) {
        for (int i = 0; i < nx; i++) {
            geometry::vec3d col = { float(i) / float(nx), float(j) / float(ny), 0.2 };
            int ir = int(255.99 * col.x);
            int ig = int(255.99 * col.y);
            int ib = int(255.99 * col.z);
            std::cout << ir << " " << ig << " " << ib << "\n";
        }
    }
}
