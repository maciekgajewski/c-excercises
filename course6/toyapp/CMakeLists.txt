project(toyapp)
cmake_minimum_required(VERSION 3.0)

link_directories(C:/lib/SDL2/lib)
add_subdirectory(displaylib)


add_executable(toyapp WIN32
    main.cc)

set_property(TARGET toyapp PROPERTY CXX_STANDARD 14)

target_link_libraries(toyapp
    displaylib)