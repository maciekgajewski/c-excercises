add_library(str
    str.cc str.h
)
set_property(TARGET str PROPERTY CXX_STANDARD 14)
target_include_directories(str INTERFACE ..)
