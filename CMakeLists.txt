# Checking the CMake
cmake_minimum_required(VERSION 3.14) 

# Project name and availability check C++ compiler
project(libPLcomparer VERSION 1.0
  DESCRIPTION "Package list comparer"
  LANGUAGES CXX)

set(BUILD_SHARED_LIBS ON)

add_library(libPLcomparer SHARED
  src/libPLcomparer.cpp)

target_include_directories(${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}/include)

# Minimum code requirements
set_target_properties(
  libPLcomparer PROPERTIES
  CXX_STANDARD 11
  CXX_STANDARD_REQUIRED ON
  SOVERSION  1
  PUBLIC_HEADER include/PLcomparer/PLcomparer.h
)

include_directories(include/)

# CLI libPLcomparer
add_executable(PLcomparer src/PLcomparer.cpp)

# Executables from the above sources
add_executable(example1 examples/compare_and_save.cpp)
add_executable(example2 examples/compare_and_print.cpp)

find_package(CURL REQUIRED)

target_link_libraries(example1 libPLcomparer CURL::libcurl)
target_link_libraries(example2 libPLcomparer CURL::libcurl)

