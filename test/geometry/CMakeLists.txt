set(geometry_srcs
    vec3d_test.cpp
)

set(geometry_libs
    geometry
)

add_unit_test(
    geometry
    geometry_srcs
    geometry_libs
)
