project(chat)

set(Boost_USE_STATIC_LIBS ON)
find_package(Boost COMPONENTS system date_time REQUIRED)
if(MSVC)
	add_definitions(-DBOOST_CONFIG_SUPPRESS_OUTDATED_MESSAGE)
endif()

if(MSVC)
    add_compile_options("/permissive-" "/W4" "/wd4505" "/WX" "$<$<CONFIG:RELEASE>:/O2>")
else()
    add_compile_options("-std=c++14" "-Wall" "-Wextra" "-Werror" "$<$<CONFIG:RELEASE>:-O3>")
endif()

add_subdirectory(json)
add_subdirectory(protocol)
add_subdirectory(client)
add_subdirectory(server)