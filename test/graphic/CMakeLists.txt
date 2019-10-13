set(graphic_srcs
    rayTest.cpp
    colorTest.cpp
)

set(graphic_libs
    geometry
    graphic
)

add_unit_test(
    graphic
    graphic_srcs
    graphic_libs
)
