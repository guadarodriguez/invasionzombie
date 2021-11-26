cmake_minimum_required(VERSION 3.20)
project(invasionzombie)

set(CMAKE_CXX_STANDARD 14)
IF (WIN32)
    set(SFML_STATIC_LIBRARIES TRUE)
    set(SFML_DIR C:/SFML/lib/cmake/SFML)
    include_directories(C:/SFML/include)
ENDIF()
find_package(SFML COMPONENTS system window graphics audio network REQUIRED)

add_executable(invasionzombie main.cpp juegox.cpp juegox.h Node.h Stack.h)
target_link_libraries(invasionzombie sfml-system sfml-window sfml-graphics sfml-audio)
