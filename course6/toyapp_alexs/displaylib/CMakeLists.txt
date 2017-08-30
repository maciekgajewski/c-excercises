add_library(displaylib
	window.cc window.h
	functions.cc functions.h
	sdlobject.cc sdlobject.h
	surface.cc surface.h
	color.cc color.h
	point2d.cc point2d.h
	point3d.cc point3d.h
)
set_property(TARGET displaylib PROPERTY CXX_STANDARD 14)
target_link_libraries(displaylib SDL2)
target_include_directories(displaylib INTERFACE ..)
