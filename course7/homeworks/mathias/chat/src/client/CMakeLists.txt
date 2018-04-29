add_executable(client client.cpp)
set_property(TARGET client PROPERTY CXX_STANDARD 14)
target_link_libraries(client PRIVATE procotol)
