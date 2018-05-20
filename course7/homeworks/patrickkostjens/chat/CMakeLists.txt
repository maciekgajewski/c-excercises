cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++14")

find_package(Boost REQUIRED COMPONENTS system)

INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})

include_directories("../../../../include")

add_executable(chat chat.cc chat_client.cc)

TARGET_LINK_LIBRARIES(chat LINK_PUBLIC ${Boost_LIBRARIES})
