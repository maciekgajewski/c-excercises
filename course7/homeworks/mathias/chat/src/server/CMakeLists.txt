add_executable(server server.cpp user_session.cpp user_session.h chat_room.cpp chat_room.h)
set_property(TARGET server PROPERTY CXX_STANDARD 14)
target_link_libraries(server PRIVATE procotol)