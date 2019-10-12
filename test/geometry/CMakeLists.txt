set(geometry_srcs
    vec3dTest.cpp
)

set(geometry_libs
    geometry
)

add_unit_test(
    geometry
    geometry_srcs
    geometry_libs
)
