cmake_minimum_required(VERSION 3.17)
project(simpleTest)

set(CMAKE_CXX_STANDARD 20)

add_library(simpleTest Test.h)
set_target_properties(simpleTest PROPERTIES LINKER_LANGUAGE CXX)

add_executable(runTest runTest.cpp)