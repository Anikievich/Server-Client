cmake_minimum_required(VERSION 3.25)
project(Server)

set(CMAKE_CXX_STANDARD 17)

add_executable(Server main.cpp Server.cpp Server.h socketHandler.cpp socketHandler.h Handler.cpp Handler.h)
