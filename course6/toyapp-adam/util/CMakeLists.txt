add_library(util
	clock.h
	keyboard.cc keyboard.h
	mouse.h
	pixel.h)

target_link_libraries(util SDL2)
