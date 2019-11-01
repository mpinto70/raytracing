set(graphic_srcs
    ray_test.cpp
    color_test.cpp
    hittable_test.cpp
    sphere_reflexive_test.cpp
    sphere_transparent_test.cpp
)

set(graphic_libs
    mck_graphic
    graphic
    geometry
)

add_unit_test(
    graphic
    graphic_srcs
    graphic_libs
)
