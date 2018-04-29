add_library(procotol STATIC protocol.h protocol.cpp)
target_link_libraries(procotol PUBLIC json Boost::system Boost::date_time)
target_include_directories(procotol PUBLIC Boost::boost)
target_include_directories(procotol INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
