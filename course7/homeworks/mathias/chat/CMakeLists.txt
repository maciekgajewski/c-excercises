cmake_minimum_required(VERSION 3.4 FATAL_ERROR)

project(chat)

set(Boost_USE_STATIC_LIBS ON)
find_package(Boost COMPONENTS system date_time REQUIRED)

if(MSVC)
    add_compile_options("/permissive-" "/W4" "/wd4505" "/WX" "$<$<CONFIG:RELEASE>:/O2>")
else()
    add_compile_options("-std=c++14" "-Wall" "-Wextra" "-Werror" "$<$<CONFIG:RELEASE>:-O3>")
endif()

add_executable(server server.cpp server.h)
set_property(TARGET server PROPERTY CXX_STANDARD 14)
#target_compile_definitions(server PRIVATE _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS)
target_link_libraries(server PRIVATE Boost::system Boost::date_time)
target_include_directories(server PRIVATE Boost::boost)

add_executable(client client.cpp)
set_property(TARGET client PROPERTY CXX_STANDARD 14)
#target_compile_definitions(client PRIVATE _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS)
target_link_libraries(client PRIVATE Boost::system Boost::date_time)
target_include_directories(client PRIVATE Boost::boost)
