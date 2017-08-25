cmake_minimum_required(VERSION 3.5)
project(homework10)

set(SOURCES linkedlist.hh homework10.cc)

add_compile_options(-Wall -Wextra -Wdisabled-optimization --coverage)
set(CMAKE_CXX_STANDARD 14)

add_executable(homework10 ${SOURCES})

target_link_libraries(homework10 --coverage)

add_custom_target(coverage
    COMMAND lcov --directory . --zerocounters
    COMMAND ./homework10
    COMMAND lcov --directory . --capture --output-file coverage.info
    COMMAND genhtml coverage.info --output-directory coverage)
add_dependencies(coverage homework10)

add_custom_target(cppcheck VERBATIM
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    DEPENDS homework10
    COMMAND cppcheck --suppress=missingIncludeSystem
        "--template=[{severity}] {file}:{line} {message} ({id}) {callstack}"
        --enable=warning,performance,portability,style,information
        --suppress=assertWithSideEffect:homework10.cc
        --suppress=assignmentInAssert:homework10.cc
        ${SOURCES} )
