cmake_minimum_required(VERSION 3.25)
project(Lab01)

set(CMAKE_CXX_STANDARD 23)

add_executable(Lab01 main.cpp color.h framebuffer.h vertex2.h)
target_sources(Lab01 PRIVATE framebuffer.cpp vertex2.cpp color.cpp)
