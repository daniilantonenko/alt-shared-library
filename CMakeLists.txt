# Checking the CMake
cmake_minimum_required(VERSION 3.14) 

# Project name and availability check C++ compiler
project(pl-comparer-lib VERSION 1.0
  DESCRIPTION "Package list comparer"
  LANGUAGES CXX)

set(BUILD_SHARED_LIBS ON)

add_library(pl-comparer-lib SHARED
  src/pl-comparer-lib.cpp)

target_include_directories(${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}/include)

# Minimum code requirements
set_target_properties(
  pl-comparer-lib PROPERTIES
  CXX_STANDARD 11
  CXX_STANDARD_REQUIRED ON
  SOVERSION  1
  PUBLIC_HEADER include/pl-comparer/pl-comparer.h
)

include_directories(include/)

# CLI pl-comparer-lib
add_executable(pl-comparer src/pl-comparer.cpp)

# Executables from the above sources
#add_executable(example1 examples/compare_and_save.cpp)
#add_executable(example2 examples/compare_and_print.cpp)

find_package(CURL REQUIRED)

#target_link_libraries(example1 pl-comparer-lib CURL::libcurl)
#target_link_libraries(example2 pl-comparer-lib CURL::libcurl)

