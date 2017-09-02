add_library(displaylib
    window.cc window.h
    functions.cc functions.h
    sdlobject.cc sdlobject.h
    surface.cc surface.h
    types.h
    shapes2d.cc shapes2d.h
    shapes3d.cc shapes3d.h
    vector2d.h
    vector3d.cc vector3d.h
    matrix.cc matrix.h
)
set_property(TARGET displaylib PROPERTY CXX_STANDARD 14)
target_link_libraries(displaylib SDL2)
target_include_directories(displaylib INTERFACE ..)
