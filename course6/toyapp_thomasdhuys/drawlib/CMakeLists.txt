add_library(drawlib
	primitives.cc primitives.h
	index.h
    rgb.h
    colors.h
    renderer.cc renderer.h
    render_object.cc render_object.h
    drawer.cc drawer.h
    projector.cc projector.h
	vector3d.cc vector3d.h
)

set_property(TARGET drawlib PROPERTY CXX_STANDARD 14)
target_link_libraries(drawlib displaylib)

target_include_directories(drawlib INTERFACE ..)
