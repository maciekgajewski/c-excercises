project(toyapp)
cmake_minimum_required(VERSION 3.0)

add_subdirectory(displaylib)


add_executable(toyapp
    main.cc)

set_property(TARGET toyapp PROPERTY CXX_STANDARD 14)

target_link_libraries(toyapp
    displaylib)