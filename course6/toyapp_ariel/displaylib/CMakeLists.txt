add_library(displaylib
	window.cc window.h
	functions.cc functions.h
	sdlobject.cc sdlobject.h
	surface.cc surface.h
        renderingengine.cc renderingengine.h
        float3.cc float3.h
        sphere.cc sphere.h
        ray.cc ray.h
        primitive.h
        intersectioninfo.cc intersectioninfo.h
        material.cc material.h
)
set_property(TARGET displaylib PROPERTY CXX_STANDARD 14)
target_link_libraries(displaylib SDL2)
target_include_directories(displaylib INTERFACE ..)
