set(graphic_srcs
    rayTest.cpp
    colorTest.cpp
    hittableTest.cpp
    sphereTest.cpp
)

set(graphic_libs
    mck_graphic
    geometry
    graphic
)

add_unit_test(
    graphic
    graphic_srcs
    graphic_libs
)
