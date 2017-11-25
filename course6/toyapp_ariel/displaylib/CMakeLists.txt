add_library(displaylib
	window.cc window.h
	functions.cc functions.h
	sdlobject.cc sdlobject.h
	surface.cc surface.h
        renderingengine.cc renderingengine.h
        float3.h
        float4.h
        sphere.h
        ray.h
        primitive.h
        intersectioninfo.h
        material.h
        scene.cc scene.h
        mat4.h
        triangle.h
        vector.h
)

set_property(TARGET displaylib PROPERTY CXX_STANDARD 14)
target_link_libraries(displaylib SDL2)
target_include_directories(displaylib INTERFACE ..)
