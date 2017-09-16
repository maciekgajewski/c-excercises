add_library(drawlib
	primitives.cc primitives.h
	vertex.cc vertex.h
    color.h color.cc
    renderer.cc renderer.h
    scene.cc scene.h
    shape.cc shape.h
    projector.cc projector.h
    vector3d.cc vector3d.h
    matrix.cc matrix.h
)

set_property(TARGET drawlib PROPERTY CXX_STANDARD 14)
target_link_libraries(drawlib displaylib)

target_include_directories(drawlib INTERFACE ..)
