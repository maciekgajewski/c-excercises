add_library(math
	transform.cc transform.h
)
set_property(TARGET math PROPERTY CXX_STANDARD 14)
target_link_libraries(math)
target_include_directories(math INTERFACE ..)
