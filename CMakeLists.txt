cmake_minimum_required(VERSION 3.20)
project(invasionzombie)

set(SFML_STATIC_LIBRARIES TRUE)
set(CMAKE_CXX_STANDARD 14)
set(SFML_DIR C:/SFML/lib/cmake/SFML)
find_package(SFML COMPONENTS system window graphics audio network REQUIRED)
include_directories(C:/SFML/include)

add_executable(invasionzombie main.cpp juegox.cpp juegox.h Node.h Stack.h)
target_link_libraries(invasionzombie sfml-system sfml-window sfml-graphics sfml-audio)
