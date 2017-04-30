cmake_minimum_required(VERSION 3.5)
project(homework11)

set(SOURCES homework11.cc)

add_compile_options(-Wall -Wextra -Wdisabled-optimization)
set(CMAKE_CXX_STANDARD 14)

add_subdirectory(x_benchmark EXCLUDE_FROM_ALL)
include_directories(SYSTEM x_benchmark/include)

add_executable(homework11 ${SOURCES})

target_link_libraries(homework11 benchmark)

add_custom_target(cppcheck VERBATIM
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    DEPENDS homework11
    COMMAND cppcheck --suppress=missingIncludeSystem
        "--template=[{severity}] {file}:{line} {message} ({id}) {callstack}"
        --enable=warning,performance,portability,style,information
        --suppress=assertWithSideEffect:homework11.cc
        --suppress=assignmentInAssert:homework11.cc
        ${SOURCES} )
