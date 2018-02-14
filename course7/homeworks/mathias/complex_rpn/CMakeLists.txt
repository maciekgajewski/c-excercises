cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

project(complex_rpn VERSION 1.0 LANGUAGES CXX)

if(MSVC)
    add_compile_options("/permissive-" "/W4" "/WX" "$<$<CONFIG:RELEASE>:/O2>")
else()
    add_compile_options("-std=c++14" "-Wall" "-Wextra" "-Werror" "$<$<CONFIG:RELEASE>:-O3>")
endif()

add_executable(complex_rpn main.cpp complex.h complex.cpp rpn_calculator.h rpn_calculator.cpp)
target_include_directories(complex_rpn PRIVATE ${Boost_INCLUDE_DIR})
