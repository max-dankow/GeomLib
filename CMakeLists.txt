cmake_minimum_required(VERSION 3.3)
project(GeomLib)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -lgtest -pthread")

set(SOURCE_FILES main.cpp Geom.h)
set(TEST_FILES Tests/Tests.cpp Geom.h)
add_executable(Tests ${TEST_FILES})

add_executable(GeomLib ${SOURCE_FILES})

target_link_libraries(Tests gtest)