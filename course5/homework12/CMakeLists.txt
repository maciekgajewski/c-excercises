FIND_PACKAGE(Boost COMPONENTS program_options REQUIRED)
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -lboost_program_options")
set(CMAKE_CXX_STANDARD 14)

add_executable(mysort main.cc)
TARGET_LINK_LIBRARIES(mysort ${Boost_LIBRARIES})
